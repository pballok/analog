TEMPLATE = app
INCLUDEPATH += ../../qtframework
HEADERS = ../../qtframework/severity.h \
    ../../qtframework/sevexception.h \
    ../../qtframework/logger.h \
    ../../qtframework/logwriter.h \
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
    outputcreator.h \
    countaction.h \
    batchanalyser.h
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
    outputcreator.cpp \
    countaction.cpp \
    batchanalyser.cpp
DESTDIR = ..
QT -= gui
QT += xml
QT += xmlpatterns
CONFIG += qt
CONFIG += console
