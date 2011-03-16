/* Xml.cpp */

#include "Xml.h"

/* XmlAtt */

//XmlAtt::

/* XmlNode */

/* XmlElement */

void XmlElement::AddNode( XmlNode node )
{
    nodeList.push_back( node );
}

void XmlElement::AddAttribute( XmlAtt att )
{
    attList.push_back( att );
}

void XmlElement::AddAttribute( string n, string v )
{
    attList.push_back( XmlAtt att(n, v) );
}

/* XmlContent */

//XmlContent::
{
}
