TEMPLATE = app
HEADERS = qtframework.h \
    sevexception.h \
    tracer.h \
    qtlogger.h \
    preferences.h \
    loganalyzer.h \
    logdatasource.h \
    actiondefsingleliner.h \
    actiondeflist.h \
    actiondef.h \
    pattern.h \
    action.h
SOURCES = tracer.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    loganalyzer.cpp \
    logdatasource.cpp \
    actiondefsingleliner.cpp \
    actiondeflist.cpp \
    actiondef.cpp \
    pattern.cpp \
    action.cpp
DESTDIR = ..
QT -= gui
QT += xml
QT += xmlpatterns
CONFIG += qt
CONFIG += console
