TEMPLATE = app
INCLUDEPATH += ../../qtframework
HEADERS = ../../qtframework/severity.h \
    ../../qtframework/sevexception.h \
    ../../qtframework/logger.h \
    ../../qtframework/logwriter.h \
    ../../qtframework/consolewriter.h \
    ../../qtframework/filewriter.h \
    ../../qtframework/logmessage.h \
    ../../qtframework/tracer.h \
    ../../qtframework/qtmysqlconnection.h \
    lara.h \
    preferences.h \
    loganalyser.h \
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
    ../../qtframework/filewriter.cpp \
    ../../qtframework/logmessage.cpp \
    ../../qtframework/tracer.cpp \
    ../../qtframework/qtmysqlconnection.cpp \
    preferences.cpp \
    main.cpp \
    loganalyser.cpp \
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
QT += sql
QT += xmlpatterns
CONFIG += qt
CONFIG += console
