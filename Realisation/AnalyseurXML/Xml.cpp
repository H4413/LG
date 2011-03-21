/* Xml.cpp */

#include "Xml.h"

#include <string.h>
#include <iostream>

void XmlDoc::Display() const
{
	root->Display();
}

/* XmlAtt */

void XmlAtt::Display() const
{
    cout << " " << Name << " = \"" << Value << "\" "; 
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
    attList.push_back( &att );
}

void XmlElement::AddAttribute( string n, string v )
{
    attList.push_back( new XmlAtt( n, v ));
}

void XmlElement::Display(int ident) const
{
    // Opening
    cout << "<" << name;

    // Attributes
    vector  <XmlAtt*>::const_iterator attIt;
    for ( attIt = attList.begin(); attIt != attList.end(); ++attIt )
        (*attIt)->Display();
        
    cout << ">" << endl;
    
    // Elements and content
    vector <XmlNode*>::const_iterator nIt;
    for ( nIt = nodeList.begin(); nIt != nodeList.end(); ++nIt )
    {
		for (int i = 0; i <= ident; i++) cout << "\t";
        (*nIt)->Display(ident+1);	
	}
	
	cout << endl;
	for (int i = 0; i < ident; i++) cout << "\t";

    // Closing
    cout << "</" << name << ">" << endl;
}

bool XmlElement::ValidateNode(bool verbose) const
{
    return true;
}

XmlElement::~XmlElement()
{
    for (int i( 0 ); i < nodeList.size(); i++ )
        delete nodeList[i];

    nodeList.clear();
}


/* XmlContent */

void XmlContent::Display(int ident) const
{
    char delims[] = "\n\t";
    char *result = NULL;
    result = strtok( content, delims );

    while( result != NULL ) 
    {		
        cout << result;
        result = strtok( NULL, delims );
    }
}
