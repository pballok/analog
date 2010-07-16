#include "outputcreator.h"
#include "qtframework.h"

cOutputCreator::cOutputCreator( cLogDataSource *p_poDataSource, tmActionList *p_poActionList )
{
    cTracer  obTracer( "cOutputCreator::cOutputCreator" );

    m_poDataSource = p_poDataSource;
    m_poActionList = p_poActionList;

}

cOutputCreator::~cOutputCreator()
{
    cTracer  obTracer( "cOutputCreator::~cOutputCreator" );
}
