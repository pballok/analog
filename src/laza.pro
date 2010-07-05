TEMPLATE = app
HEADERS = qtframework.h \
    sevexception.h \
    tracer.h \
    qtlogger.h \
    preferences.h \
    loganalyzer.h \
    logdatasource.h \
    actions.h
SOURCES = tracer.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    loganalyzer.cpp \
    logdatasource.cpp \
    actions.cpp
DESTDIR = ..
QT -= gui
QT += xml
CONFIG += qt
CONFIG += console
