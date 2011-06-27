TEMPLATE = app

INCLUDEPATH += ../../qtframework
INCLUDEPATH += ../src

HEADERS = ../../qtframework/severity.h \
    ../../qtframework/sevexception.h \
    ../../qtframework/logger.h \
    ../../qtframework/logwriter.h \
    ../../qtframework/consolewriter.h \
    ../../qtframework/filewriter.h \
    ../../qtframework/logmessage.h \
    ../../qtframework/tracer.h \
    ../../qtframework/qtmysqlconnection.h \
    ../src/lara.h \
    ../src/preferences.h \
    ../src/actiondef.h \
    ../src/actiondefsingleliner.h \
    ../src/actiondeflist.h \
    ../src/pattern.h \
    ../src/countaction.h \
    ../src/action.h \
    ../src/logdatasource.h \
    ../src/outputcreator.h \
    ../src/loganalyser.h \
    ../src/batchanalyser.h \
    unittest.h \
    actiondeftest.h \
    loganalysertest.h \
    datasourcetest.h \
    outputcreatortest.h

SOURCES = ../../qtframework/logger.cpp \
    ../../qtframework/consolewriter.cpp \
    ../../qtframework/filewriter.cpp \
    ../../qtframework/logmessage.cpp \
    ../../qtframework/tracer.cpp \
    ../../qtframework/qtmysqlconnection.cpp \
    ../src/preferences.cpp \
    ../src/actiondef.cpp \
    ../src/actiondefsingleliner.cpp \
    ../src/actiondeflist.cpp \
    ../src/pattern.cpp \
    ../src/countaction.cpp \
    ../src/action.cpp \
    ../src/logdatasource.cpp \
    ../src/outputcreator.cpp \
    ../src/loganalyser.cpp \
    ../src/batchanalyser.cpp \
    laratest.cpp \
    unittest.cpp \
    actiondeftest.cpp \
    loganalysertest.cpp \
    datasourcetest.cpp \
    outputcreatortest.cpp

DESTDIR = ..

QT -= gui
QT += sql
QT += xml
QT += xmlpatterns

CONFIG += qt
CONFIG += console
