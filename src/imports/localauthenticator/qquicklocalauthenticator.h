#ifndef QQUICKLOCALAUTHENTICATOR_H
#define QQUICKLOCALAUTHENTICATOR_H

#include "qlocalauthenticator.h"

class QQuickLocalAuthenticator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString reason READ reason WRITE setReason NOTIFY reasonChanged)
    Q_PROPERTY(AuthenticationPolicy policy READ policy WRITE setPolicy NOTIFY policyChanged)
    Q_PROPERTY(bool biometricSupported READ biometricSupported CONSTANT)
    Q_PROPERTY(bool biometricActivated READ biometricActivated CONSTANT)
    Q_PROPERTY(bool passcodeActivated READ passcodeActivated CONSTANT)

public:
    enum AuthenticationPolicy {
        PolicyWithBiometrics,
        PolicyWithBiometricsOrPassword
    };
    Q_ENUM(AuthenticationPolicy)

    enum AuthenticationFailureReason {
        NoFailure,
        CredentialsWrong,
        CancelledByUser,
        //UserFallback
        CancelledBySystem
    };
    Q_ENUM(AuthenticationFailureReason)

    explicit QQuickLocalAuthenticator(QObject *parent = 0);
    ~QQuickLocalAuthenticator();

    Q_INVOKABLE void requestAuthentication();

    void setReason(const QString &reason);
    QString reason() const;

    void setPolicy(const AuthenticationPolicy policy);
    AuthenticationPolicy policy() const;

    bool biometricSupported();
    bool biometricActivated();
    bool passcodeActivated();

signals:
    void authenticationFinished(bool success,
                                QQuickLocalAuthenticator::AuthenticationFailureReason reason);

    void reasonChanged();
    void policyChanged();

private:
    QLocalAuthenticator d;
};

Q_DECLARE_METATYPE(QQuickLocalAuthenticator::AuthenticationFailureReason)

#endif // QQUICKLOCALAUTHENTICATOR_H
