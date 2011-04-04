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
        US [label="USER"];
        BA [label="{Batch Analyser Module|cBatchAnalyser}"];
        AD [label="{Action Definition Module|cPattern\n cActionDef\n cActionDefSingleLiner\n cCountAction\n cActionDefList}"];
        LA [label="{Log Analyser Module|cLogAnalyser\n cAction}"];
        DS [label="{Data Source Module|cLogDataSource}"];
        OC [label="{Output Creator Module|cOutputCreator}"];
        US -> BA [label="Starts"];
        US -> AD [label="Provides Action Definitions (XML)"];
        AD -> LA [label="Provides Action Definitions"];
        DS -> LA [label="Provides Input Log File Names"];
        BA -> LA [label="Starts"];
        LA -> OC [label="Sends Results To"];
    }
    \enddot
 */

extern cLogger       g_obLogger;
extern cPreferences* g_poPrefs;

#endif // LARA_H
