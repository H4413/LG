/* Xml.cpp */

#include "Xml.h"

#include <iostream>

/* XmlAtt */

int main()
{
    return 0;
}

void XmlAtt::Display() const
{
    cout << Name << " = \"" << Value << "\" "; 
}

/* XmlNode */

/* XmlElement */

void XmlElement::AddElement( XmlElement* elt )
{
    nodeList.push_back( elt );
}

void XmlElement::AddContent( XmlContent* cont )
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
    vector <XmlNode*>::const_iterator nIt;
    for ( nIt = nodeList.begin(); nIt != nodeList.end(); ++nIt )
        (*nIt)->Display();	

    // Closing
    cout << "/>" <<endl;
}

XmlElement::~XmlElement()
{
    for (int i( 0 ); i < nodeList.size(); i++ )
        delete nodeList[i];

    nodeList.clear();
}


/* XmlContent */

void XmlContent::Display() const
{
    cout << "\"" << content << "\"" << endl;
}
