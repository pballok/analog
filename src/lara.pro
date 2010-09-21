TEMPLATE = app
INCLUDEPATH += ../../qtframework
HEADERS = ../../qtframework/sevexception.h \
    ../../qtframework/logger.h \
    ../../qtframework/consolewriter.h \
    ../../qtframework/logmessage.h \
    ../../qtframework/tracer.h \
    lara.h \
    preferences.h \
    loganalyzer.h \
    logdatasource.h \
    actiondefsingleliner.h \
    actiondeflist.h \
    actiondef.h \
    pattern.h \
    action.h \
    outputcreator.h
SOURCES = ../../qtframework/logger.cpp \
    ../../qtframework/consolewriter.cpp \
    ../../qtframework/logmessage.cpp \
    ../../qtframework/tracer.cpp \
    preferences.cpp \
    main.cpp \
    loganalyzer.cpp \
    logdatasource.cpp \
    actiondefsingleliner.cpp \
    actiondeflist.cpp \
    actiondef.cpp \
    pattern.cpp \
    action.cpp \
    outputcreator.cpp
DESTDIR = ..
QT -= gui
QT += xml
QT += xmlpatterns
CONFIG += qt
CONFIG += console
