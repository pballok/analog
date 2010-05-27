TEMPLATE = app
FORMS = wndmain.ui \
    dlgpreferences.ui \
    dlglogs.ui
HEADERS = qtframework.h \
    sevexception.h \
    tracer.h \
    dbconnection.h \
    qtmysqlconnection.h \
    qtmysqlquerymodel.h \
    qtlogger.h \
    preferences.h \
    wndmain.h \
    dlgpreferences.h \
    dlglogs.h \
    logtablemodel.h
SOURCES = tracer.cpp \
    dbconnection.cpp \
    qtmysqlconnection.cpp \
    qtmysqlquerymodel.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    wndmain.cpp \
    dlgpreferences.cpp \
    dlglogs.cpp \
    logtablemodel.cpp
DESTDIR = ..
QT += xml
QT += sql
CONFIG += qt
CONFIG += console
