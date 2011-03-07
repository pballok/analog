#ifndef LARA_H
#define LARA_H

#include <logger.h>
#include <tracer.h>
#include <sevexception.h>

#include "preferences.h"

/*! \mainpage

    \section module_diagram Module Diagram

    \dot
    digraph lara_modules {
        node [shape=record, fontname=Helvetica, fontsize=10];
        Pattern [label="Action\n(cPattern, cActionDef)"];
    }
    \enddot
 */

extern cLogger       g_obLogger;
extern cPreferences* g_poPrefs;

#endif // LARA_H
