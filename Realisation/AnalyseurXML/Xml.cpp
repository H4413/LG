/* Xml.cpp */

#include "Xml.h"

#include <iostream>


/*DTD*/
void DTD::Display() const
{
	cout << "<!DOCTYPE " << dtdname << " SYSTEM " << filename << ">" << endl;
}

/*StyleSheet*/

void StyleSheet::Display() const
{
	cout <<"<?xml-stylesheet href=" << filename << "type=" << type << "?>" << endl; 
}

/* XmlAtt */

void XmlAtt::Display() const
{
    cout << Name << " = \"" << Value << "\" "; 
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
    vector<XmlAtt>::const_iterator attIt;
    for ( attIt = attList.begin(); attIt != attList.end(); ++attIt )
        attIt->Display();

	
    // Elements
	
    vector<XmlElement>::const_iterator eltIt;
    for ( eltIt = eltIt.begin(); eltIt != eltIt.end(); ++eltIt )
        eltIt->Display();
	


    // Elements

    vector<XmlElement>::const_iterator eltIt;
    for ( eltIt = eltIt.begin(); eltIt != eltIt.end(); ++eltIt )
        eltIt->Display();

    // Closing
    cout << "/>" <<endl;
}

/* XmlContent */

void XmlContent::Display()
{
    cout << "\"" << content << "\"" << endl;
}
