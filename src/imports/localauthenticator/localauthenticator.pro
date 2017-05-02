CXX_MODULE = purchasing
TARGET = qtlocalauthenticatorplugin
TARGETPATH = jsee23/authenticator
IMPORT_VERSION = 0.1

QT += qml quick localauthenticator

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

OTHER_FILES += \
    qmldir

SOURCES += \
    qquicklocalauthenticator.cpp \
    qtlocalauthenticatorplugin.cpp

HEADERS += \
    qquicklocalauthenticator.h

load(qml_plugin)
