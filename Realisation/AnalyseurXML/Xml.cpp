/* Xml.cpp */

#include "Xml.h"

#include <iostream>

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

    // Elements and content
    vector <XmlNode>::const_iterator nIt;
    for ( nIt =  )	

    // Closing
    cout << "/>" <<endl;
}

/* XmlContent */

virtual void XmlContent::Display()
{
    cout << "\"" << content << "\"" << endl;
}
