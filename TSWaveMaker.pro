QT       += core gui widgets

TARGET = TSWaveMaker
TEMPLATE = app

CONFIG += c++11

DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += $$files(src/*.cpp, true)
HEADERS += $$files(src/*.h, true)
FORMS   += $$files(src/*.ui, true)

release:DESTDIR = release
release:OBJECTS_DIR = release/.obj
release:MOC_DIR = release/.moc
release:RCC_DIR = release/.rcc
release:UI_DIR = release/.ui

debug:DESTDIR = debug
debug:OBJECTS_DIR = debug/.obj
debug:MOC_DIR = debug/.moc
debug:RCC_DIR = debug/.rcc
debug:UI_DIR = debug/.ui

DEFINES += VERSION='"\\\"$$system(git describe --tags --abbrev=0)\\\""'
DEFINES += GIT_VERSION='"\\\"$$system(git describe --tags)\\\""'
