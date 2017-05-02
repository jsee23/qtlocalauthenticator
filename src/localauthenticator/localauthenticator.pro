TARGET = QtLocalAuthenticator
MODULE = localauthenticator

QT += core

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

PUBLIC_HEADERS += \
    qlocalauthenticator.h

SOURCES += \
    qlocalauthenticator.cpp

ios {
    OBJECTIVE_SOURCES += \
        qlocalauthenticator_ios.mm
    LIBS += -framework LocalAuthentication
}

load(qt_module)
