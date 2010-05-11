#ifndef QTFRAMEWORK_H
#define QTFRAMEWORK_H

#include "qtlogger.h"
#include "tracer.h"
#include "qtmysqlconnection.h"
#include "preferences.h"

extern cQTLogger             g_obLogger;
extern cQTMySQLConnection   *g_poDB;
extern cPreferences         *g_poPrefs;

#endif
