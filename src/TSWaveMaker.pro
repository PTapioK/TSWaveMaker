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
	CDataFile/CDataFile.cpp \
    utils.cpp \
    containers.cpp \
    settingsdialog.cpp

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
	CDataFile/CDataFile.h \
    utils.h \
    containers.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    infodialog.ui \
    triggersection.ui \
	teamsection.ui \
	scriptsection.ui \
	taskforcesection.ui \
    settingsdialog.ui

DEFINES += VERSION='"\\\"$$system(git describe --tags --abbrev=0)\\\""'
DEFINES += GIT_VERSION='"\\\"$$system(git describe --tags)\\\""'
