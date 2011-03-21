/* Xml.cpp */

#include "Xml.h"

#include <iostream>


/*DTD*/

DTD::DTD(string name):dtdname(name){}

void DTD::Display() const
{
	cout << "<!DOCTYPE " << dtdname << " SYSTEM " << filename << ">" << endl;
}

/*StyleSheet*/

void StyleSheet::Display() const
{
	cout <<"<?xml-stylesheet href=" << filename << "type=" << type << "?>" << endl; 
}

XmlDoc
void XmlDoc::setroot(XmlElement& elt)
{
	XmlElement=elt;
}

void XmlDoc::setDTD(DTD& dtd)
{
	dtd=&dtd;
}

bool ValidateDocument(bool verbose) const
{
    return true;
}

/* XmlAtt */

void XmlAtt::Display() const
{
    cout << Name << " = \"" << Value << "\" "; 
}

/* XmlNode */

/* XmlElement */

void XmlElement::AddElement( XmlElement elt )
{
    nodeList.push_back( elt );
}

void XmlElement::AddContent( XmlContent cont )
{
    nodeList.push_back( cont );
}

void XmlElement::AddAttribute( XmlAtt att )
{
    attList.push_back( att );
}

void XmlElement::AddAttribute( string n, string v )
{
    attList.push_back( XmlAtt( n, v ));
}

void XmlElement::Display() const
{
    // Indentation
    cout << "\t";
    
    // Opening
    cout << "<" << name << " ";

    // Attributes
    vector  <XmlAtt>::const_iterator attIt;
    for ( attIt = attList.begin(); attIt != attList.end(); ++attIt )
        attIt->Display();

	
    // Elements
	
    vector  <XmlElement>::const_iterator eltIt;
    for ( eltIt = eltIt.begin(); eltIt != eltIt.end(); ++eltIt )
        eltIt->Display();
	

    // Closing
    cout << "/>" <<endl;
}

/* XmlContent */

virtual void XmlContent::Display()
{
    cout << "\"" << content << "\"" << endl;
}
