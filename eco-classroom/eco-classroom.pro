QT       += core gui widgets
#QT       += mqtt

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    ihmecoclassroom.cpp

HEADERS += \
    ihmecoclassroom.h

FORMS += \
    ihmecoclassroom.ui

RESOURCES += \
        ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
