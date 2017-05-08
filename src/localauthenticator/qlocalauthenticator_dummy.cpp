#include "qlocalauthenticator.h"

QLocalAuthenticator::QLocalAuthenticator(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QLocalAuthenticator::AuthenticationFailureReason>("QLocalAuthenticator::AuthenticationFailureReason");
}

QLocalAuthenticator::~QLocalAuthenticator()
{
}

void QLocalAuthenticator::requestAuthentication()
{
    emit authenticationFinished(false, QLocalAuthenticator::PolicyNotSupported);
}

bool QLocalAuthenticator::isPolicySupported(QLocalAuthenticator::AuthenticationPolicy policy,
                                            AuthenticationPolicyFailureReason *reason)
{
    Q_UNUSED(policy);
    Q_UNUSED(reason);

    return false;
}
