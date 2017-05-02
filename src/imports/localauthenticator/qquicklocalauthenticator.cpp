#include "qquicklocalauthenticator.h"

QQuickLocalAuthenticator::QQuickLocalAuthenticator(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QLocalAuthenticator::AuthenticationFailureReason>("QQuickLocalAuthenticator::AuthenticationFailureReason");

    connect(&d, &QLocalAuthenticator::reasonChanged,
            this, &QQuickLocalAuthenticator::reasonChanged);
    connect(&d, &QLocalAuthenticator::policyChanged,
            this, &QQuickLocalAuthenticator::policyChanged);
    connect(&d, SIGNAL(authenticationFinished(bool,QLocalAuthenticator::AuthenticationFailureReason)),
            this, SIGNAL(authenticationFinished(bool,QQuickLocalAuthenticator::AuthenticationFailureReason)));
}

QQuickLocalAuthenticator::~QQuickLocalAuthenticator()
{
}

void QQuickLocalAuthenticator::requestAuthentication()
{
    d.requestAuthentication();
}

void QQuickLocalAuthenticator::setReason(const QString &reason)
{
    d.setReason(reason);
}

QString QQuickLocalAuthenticator::reason() const
{
    return d.reason();
}

void QQuickLocalAuthenticator::setPolicy(const QQuickLocalAuthenticator::AuthenticationPolicy policy)
{
    d.setPolicy((QLocalAuthenticator::AuthenticationPolicy) policy);
}

QQuickLocalAuthenticator::AuthenticationPolicy QQuickLocalAuthenticator::policy() const
{
    return (QQuickLocalAuthenticator::AuthenticationPolicy) d.policy();
}

bool QQuickLocalAuthenticator::biometricSupported()
{
    QLocalAuthenticator::AuthenticationPolicyFailureReason reason;
    d.isPolicySupported(QLocalAuthenticator::PolicyWithBiometrics, &reason);
    return reason != QLocalAuthenticator::BiometricHardwareNotAvailable;
}

bool QQuickLocalAuthenticator::biometricActivated()
{
    QLocalAuthenticator::AuthenticationPolicyFailureReason reason;
    d.isPolicySupported(QLocalAuthenticator::PolicyWithBiometrics, &reason);
    return reason != QLocalAuthenticator::BiometricNotActivated &&
            reason != QLocalAuthenticator::BiometricHardwareNotAvailable;
}

bool QQuickLocalAuthenticator::passcodeActivated()
{
    QLocalAuthenticator::AuthenticationPolicyFailureReason reason;
    d.isPolicySupported(QLocalAuthenticator::PolicyWithBiometricsOrPassword, &reason);
    return reason != QLocalAuthenticator::PasscodeNotActivated;
}
