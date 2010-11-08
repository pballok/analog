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
    ../src/action.h \
    ../src/actiondef.h \
    ../src/actiondefsingleliner.h \
    ../src/actiondeflist.h \
    ../src/pattern.h \
    ../src/countaction.h \
    unittest.h \
    actiontest.h

SOURCES = ../../qtframework/logger.cpp \
    ../../qtframework/consolewriter.cpp \
    ../../qtframework/logmessage.cpp \
    ../../qtframework/tracer.cpp \
    ../src/action.cpp \
    ../src/actiondef.cpp \
    ../src/actiondefsingleliner.cpp \
    ../src/actiondeflist.cpp \
    ../src/pattern.cpp \
    ../src/countaction.cpp \
    laratest.cpp \
    unittest.cpp \
    actiontest.cpp

DESTDIR = .

QT -= gui
QT += xml
QT += xmlpatterns

CONFIG += qt
CONFIG += console
