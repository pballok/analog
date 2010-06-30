TEMPLATE = app
HEADERS = qtframework.h \
    sevexception.h \
    tracer.h \
    qtlogger.h \
    preferences.h \
    loganalyzer.h
SOURCES = tracer.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    loganalyzer.cpp
DESTDIR = ..
QT -= gui
QT += xml
CONFIG += qt
CONFIG += console
