#ifndef QLOCALAUTHENTICATOR_H
#define QLOCALAUTHENTICATOR_H

#include <QObject>
#include "qtlocalauthenticatorglobal_p.h"

QT_BEGIN_NAMESPACE

class Q_LOCALAUTHENTICATOR_EXPORT QLocalAuthenticator : public QObject
{
    Q_OBJECT

public:
    enum AuthenticationPolicy {
        PolicyWithBiometrics = 0x01,
        PolicyWithBiometricsOrPassword = 0x02
    };
    Q_ENUM(AuthenticationPolicy)

    enum AuthenticationPolicyFailureReason {
        PasscodeNotActivated,
        BiometricHardwareNotAvailable,
        BiometricNotActivated
    };
    Q_ENUM(AuthenticationPolicyFailureReason)

    enum AuthenticationFailureReason {
        NoFailure,
        CredentialsWrong,
        CancelledByUser,
        //UserFallback
        CancelledBySystem,
        PolicyNotSupported
    };
    Q_ENUM(AuthenticationFailureReason)

    explicit QLocalAuthenticator(QObject *parent = 0);
    virtual ~QLocalAuthenticator();

    bool isPolicySupported(AuthenticationPolicy policy,
                           AuthenticationPolicyFailureReason *reason = nullptr);

    void setReason(const QString &reason);
    QString reason() const;

    void setPolicy(const AuthenticationPolicy policy);
    AuthenticationPolicy policy() const;

public slots:
    void requestAuthentication();

signals:
    void authenticationFinished(bool success,
                                QLocalAuthenticator::AuthenticationFailureReason reason);

    void reasonChanged();
    void policyChanged();

private:
    QString m_reason;
    AuthenticationPolicy m_policy;
};

Q_DECLARE_METATYPE(QLocalAuthenticator::AuthenticationFailureReason)

QT_END_NAMESPACE

#endif // QLOCALAUTHENTICATOR_H
