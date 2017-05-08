#include "qlocalauthenticator.h"

#include <LocalAuthentication/LAContext.h>
#include <LocalAuthentication/LAError.h>

static inline LAPolicy qauthenticationpolicyToNative(QLocalAuthenticator::AuthenticationPolicy policy)
{
    return (policy == QLocalAuthenticator::PolicyWithBiometrics) ?
                LAPolicyDeviceOwnerAuthenticationWithBiometrics :
                LAPolicyDeviceOwnerAuthentication;
}

QLocalAuthenticator::QLocalAuthenticator(QObject *parent)
    : QObject(parent)
    , m_policy(PolicyWithBiometrics)
{
    qRegisterMetaType<QLocalAuthenticator::AuthenticationFailureReason>("QLocalAuthenticator::AuthenticationFailureReason");
}

QLocalAuthenticator::~QLocalAuthenticator()
{
}

void QLocalAuthenticator::requestAuthentication()
{
    LAContext *myContext = [[LAContext alloc] init];
    NSString *myLocalizedReasonString = m_reason.isEmpty() ? nullptr : m_reason.toNSString();

    AuthenticationPolicyFailureReason authReason;

    if (isPolicySupported(m_policy, &authReason)) {
        [myContext evaluatePolicy:qauthenticationpolicyToNative(m_policy)
                      localizedReason:myLocalizedReasonString
                                reply:^(BOOL success, NSError *error) {
                if (success) {
                    emit authenticationFinished(true, NoFailure);
                } else {
                    AuthenticationFailureReason reason = NoFailure;
                    switch ([error code]) {
                    case LAErrorAuthenticationFailed:
                        reason = CredentialsWrong;
                        break;
                    case LAErrorUserCancel:
                        reason = CancelledByUser;
                        break;
                    case LAErrorSystemCancel:
                        reason = CancelledBySystem;
                        break;
                    }
                    emit authenticationFinished(false, reason);
                }
            }];
    } else {
        emit authenticationFinished(false, QLocalAuthenticator::PolicyNotSupported);
    }
}

bool QLocalAuthenticator::isPolicySupported(QLocalAuthenticator::AuthenticationPolicy policy,
                                            AuthenticationPolicyFailureReason *reason)
{
    LAContext *myContext = [[LAContext alloc] init];
    NSError *authError = nullptr;
    LAPolicy systemPolicy = qauthenticationpolicyToNative(policy);

    if ([myContext canEvaluatePolicy:systemPolicy error:&authError])
        return true;

    if (reason) {
        switch ([authError code]) {
        case LAErrorPasscodeNotSet:
            (*reason) = PasscodeNotActivated;
            break;
        case LAErrorTouchIDNotAvailable:
            (*reason) = BiometricHardwareNotAvailable;
            break;
        case LAErrorTouchIDNotEnrolled:
            (*reason) = BiometricNotActivated;
            break;
        }
    }

    return false;
}
