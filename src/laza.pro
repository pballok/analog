TEMPLATE = app
HEADERS = qtframework.h \
    sevexception.h \
    tracer.h \
    qtlogger.h \
    preferences.h \
    loganalyzer.h \
    logdatasource.h \
    actionsingleliner.h \
    actionlist.h \
    action.h
SOURCES = tracer.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    loganalyzer.cpp \
    logdatasource.cpp \
    actionsingleliner.cpp \
    actionlist.cpp \
    action.cpp
DESTDIR = ..
QT -= gui
QT += xml
QT += xmlpatterns
CONFIG += qt
CONFIG += console
