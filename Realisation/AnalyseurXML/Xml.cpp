/* Xml.cpp */

#include "Xml.h"
#include <algorithm>
#include <iostream>

/* XmlAtt */

void XmlAtt::Display() const
{
    cout << Name << " = \"" << Value << "\""; 
}

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

void XmlElement::Display() const
{
    // Indentation
    cout << "\t";
    
    // Opening
    cout << "<" << name << " ";

    // Attributes
    for_each( attList.begin(), attList.end(), Display); 

    // Elements

    // Closing
    cout << "/>" <<endl;
}

/* XmlContent */

//XmlContent::
{
}
