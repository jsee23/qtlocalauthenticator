#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include "qquicklocalauthenticator.h"

static void initResources()
{
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_jsee23_authenticator);
#endif
}

QT_BEGIN_NAMESPACE

class QtLocalAuthenticatorPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtLocalAuthenticatorPlugin(QObject *parent = 0) : QQmlExtensionPlugin(parent) { initResources(); }
    virtual void registerTypes(const char *uri) override;
};

void QtLocalAuthenticatorPlugin::registerTypes(const char *uri)
{
    // jsee23.authenticator 0.1
    qmlRegisterType<QQuickLocalAuthenticator>(uri, 0, 1, "LocalAuthenticator");
}

QT_END_NAMESPACE

#include "qtlocalauthenticatorplugin.moc"
