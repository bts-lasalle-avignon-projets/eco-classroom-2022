QT       += core gui widgets
QT       += mqtt

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    communicationmqtt.cpp \
    main.cpp \
    ihmecoclassroom.cpp \
    salle.cpp

HEADERS += \
    communicationmqtt.h \
    ihmecoclassroom.h \
    salle.h

FORMS += \
    ihmecoclassroom.ui

RESOURCES += \
        ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
