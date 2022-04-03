QT       += core gui widgets sql

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basededonnees.cpp \
    main.cpp \
    ihm.cpp \
    utilisateur.cpp

HEADERS += \
    basededonnees.h \
    ihm.h \
    utilisateur.h

FORMS += \
    ihm.ui

RESOURCES += \
    ressources.qrc

COPIES += bd
bd.files = exemple.sqlite
bd.path = $$OUT_PWD/
bd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
