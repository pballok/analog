TEMPLATE = app

INCLUDEPATH += ../../qtframework
INCLUDEPATH += ../src

HEADERS = ../../qtframework/severity.h \
    ../../qtframework/sevexception.h \
    ../../qtframework/logger.h \
    ../../qtframework/logwriter.h \
    ../../qtframework/consolewriter.h \
    ../../qtframework/logmessage.h \
    ../../qtframework/tracer.h \
    ../src/lara.h \
    ../src/actiondef.h \
    ../src/actiondefsingleliner.h \
    ../src/actiondeflist.h \
    ../src/pattern.h \
    ../src/countaction.h \
    ../src/action.h \
    unittest.h \
    actiondeftest.h \
    loganalysertest.h \
    datasourcetest.h

SOURCES = ../../qtframework/logger.cpp \
    ../../qtframework/consolewriter.cpp \
    ../../qtframework/logmessage.cpp \
    ../../qtframework/tracer.cpp \
    ../src/actiondef.cpp \
    ../src/actiondefsingleliner.cpp \
    ../src/actiondeflist.cpp \
    ../src/pattern.cpp \
    ../src/countaction.cpp \
    ../src/action.cpp \
    laratest.cpp \
    unittest.cpp \
    actiondeftest.cpp \
    loganalysertest.cpp \
    datasourcetest.cpp

DESTDIR = ..

QT -= gui
QT += sql
QT += xml
QT += xmlpatterns

CONFIG += qt
CONFIG += console
