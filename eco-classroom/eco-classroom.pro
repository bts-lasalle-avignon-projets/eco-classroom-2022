QT       += core gui widgets sql
QT       += mqtt

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    basededonnees.cpp \
    communicationmqtt.cpp \
    main.cpp \
    ihmecoclassroom.cpp \
    mesure.cpp \
    salle.cpp

HEADERS += \
    basededonnees.h \
    communicationmqtt.h \
    ihmecoclassroom.h \
    mesure.h \
    salle.h

FORMS += \
    ihmecoclassroom.ui

RESOURCES += \
        ressources.qrc

COPIES += bd
bd.files = eco-classroom.db
bd.path = $$OUT_PWD/
bd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
