#include "qlocalauthenticator.h"

void QLocalAuthenticator::setReason(const QString &reason)
{
    if (reason == m_reason)
        return;

    m_reason = reason;
    emit reasonChanged();
}

QString QLocalAuthenticator::reason() const
{
    return m_reason;
}

void QLocalAuthenticator::setPolicy(const QLocalAuthenticator::AuthenticationPolicy policy)
{
    if (policy == m_policy)
        return;

    m_policy = policy;
    emit policyChanged();
}

QLocalAuthenticator::AuthenticationPolicy QLocalAuthenticator::policy() const
{
    return m_policy;
}
