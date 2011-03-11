#ifndef LARA_H
#define LARA_H

#include <logger.h>
#include <tracer.h>
#include <sevexception.h>

#include "preferences.h"

/*! \mainpage

    For an overview on the L.A.R.A. tool see
    <a href="http://vascular.em.health.ge.com/wiki/index.php/VACAS:Knowledge_Base/Tools/LARA">LARA documentation on Wiki</a>

    \section module_diagram Module Interaction Diagram

    \dot
    digraph lara_modules {
        node [shape=record, fontname=Helvetica, fontsize=10];
        edge [fontsize=10];
        AD [label="{Action Definition Module|cActionDef\n cActionDefSingleLiner\n cCountAction\n cActionDefList}"];
        LA [label="{Log Analyser Module|cPattern}"];
        AD -> LA [label="Provides Action Definitions"];
    }
    \enddot
 */

extern cLogger       g_obLogger;
extern cPreferences* g_poPrefs;

#endif // LARA_H
