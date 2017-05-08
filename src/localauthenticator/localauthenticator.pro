TARGET = QtLocalAuthenticator
MODULE = localauthenticator

QT += core

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    qlocalauthenticator.h \
    qtlocalauthenticatorglobal_p.h

SOURCES += \
    qlocalauthenticator.cpp

ios {
    OBJECTIVE_SOURCES += \
        qlocalauthenticator_ios.mm
    LIBS += -framework LocalAuthentication
} else {
    SOURCES += \
        qlocalauthenticator_dummy.cpp
}

load(qt_module)
