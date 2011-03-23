/* Xml.cpp */

/* Project includes */
#include "Xml.h"
#include "DTD.h"

/* System includes */
#include <string.h>
#include <iostream>

/* DTD */

void DTD::Display() const
{
    cout << "<!DOCTYPE " << name;
    cout << " SYSTEM" << " \"" << fileName << "\">" << endl;
}

/* XmlDoc */

void XmlDoc::Display() const
{
    cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
    dtd->Display();
    root->Display();
}

/* XmlAtt */

void XmlAtt::Display() const
{
    cout << " " << Name << " = \"" << Value << "\" "; 
}

/* XmlNode */

/* XmlElement */

vector<XmlElement*> XmlElement::GetChildrenElements() const
{
    vector<XmlElement*> elements;
    for (   vector <XmlNode*>::const_iterator it = nodeList.begin();
            it != nodeList.end();
            ++it )
     {
        if ( (*it)->isElement() ) elements.push_back( (XmlElement*) *it );
     }

    return elements;
}

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

XmlElement * XmlElement::GetNextElemChild( XmlElement * elem )
{
    XmlElement * result = NULL;
    return result;
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
