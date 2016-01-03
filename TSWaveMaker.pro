QT       += core gui widgets

TARGET = TSWaveMaker
TEMPLATE = app

CONFIG += c++11

DEFINES += _CRT_SECURE_NO_WARNINGS

FORMS   += src/*.ui

SOURCES += src/*.cpp
HEADERS += src/*.h
SOURCES += src/CDataFile/*.cpp
HEADERS += src/CDataFile/*.h

release:DESTDIR = build/release
release:OBJECTS_DIR = build/release/.obj
release:MOC_DIR = build/release/.moc
release:RCC_DIR = build/release/.rcc
release:UI_DIR = build/release/.ui

debug:DESTDIR = build/debug
debug:OBJECTS_DIR = build/debug/.obj
debug:MOC_DIR = build/debug/.moc
debug:RCC_DIR = build/debug/.rcc
debug:UI_DIR = build/debug/.ui

DEFINES += VERSION='"\\\"$$system(git describe --tags --abbrev=0)\\\""'
DEFINES += GIT_VERSION='"\\\"$$system(git describe --tags)\\\""'
