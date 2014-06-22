#-------------------------------------------------
#
# Project created by QtCreator 2012-07-17T00:49:15
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = TSWaveMaker
TEMPLATE = app

DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    trigger.cpp \
    action.cpp \
    event.cpp \
    tag.cpp \
    team.cpp \
    script.cpp \
    taskforce.cpp \
    infodialog.cpp \
    triggersection.cpp \
    teamsection.cpp \
	scriptsection.cpp \
	taskforcesection.cpp \
	fileoperations.cpp \
	CDataFile/CDataFile.cpp

HEADERS  += mainwindow.h \
    main.h \
    trigger.h \
    action.h \
    event.h \
    tag.h \
    team.h \
    script.h \
    taskforce.h \
    infodialog.h \
    triggersection.h \
    teamsection.h \
    scriptsection.h \
    taskforcesection.h \
	fileoperations.h \
	CDataFile/CDataFile.h

FORMS    += mainwindow.ui \
    infodialog.ui \
    triggersection.ui \
	teamsection.ui \
	scriptsection.ui \
	taskforcesection.ui

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
