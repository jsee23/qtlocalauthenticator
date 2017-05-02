# QtLocalAuthenticator
C++ and QML library for biometric authentication (e.g. Touch ID)

1. installation
```
qmake
make
make install
```

2. C++ module

1.a. adding to your .pro file
```
...
QT += localauthenticator
...
``` 
2.b. sample code
```
QLocalAuthenticator authenticator;
authenticator.setReason("Access your private information!");
authenticator.setPolicy(QLocalAuthenticator::PolicyWithBiometricsOrPassword);

connect(&authenticator, &QLocalAuthenticator::authenticationFinished,
        &myFancyClass, &MyFancyClass::authenticationFinished);

...
void MyFancyClass::authenticationFinished(bool success,
        QLocalAuthenticator::AuthenticationFailureReason reason)
{
    if (success)
        qWarning("Authentication was successful!");
    else
        qWarning("Authentication failed! reason = %d", reason);
}
```

3. QML module

3.1. sample code
```
...
import jsee23.authenticator 0.1

...
    LocalAuthenticator {
        id: authenticator
        reason: "Get access to your private information!"
        policy: LocalAuthenticator.PolicyWithBiometricsOrPassword
        onAuthenticationFinished: {
            if (success)
                console.log("Authentication was successful!");
            else
                console.log("Authentication failed! reason = " + reason)
        }
    }
...
```


currently supported platforms: iOS
