/* Xml.cpp */

/* Project includes */
#include "Xml.h"
#include "DTD.h"

/* System includes */
#include <string.h>
#include <iostream>

using namespace std;


/* DTD */

void DTD::Display() const
{
    cout << "<!DOCTYPE " << Name;
    cout << " SYSTEM" << " \"" << FileName << "\">" << endl;
}

/* XmlDoc */

void XmlDoc::Display() const
{
    cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
    if (dtd)
		dtd->Display();
	if (root)
		root->Display();
}

XmlDoc::~XmlDoc()
{
	if (root)
		delete root;
	if (dtd)
		delete dtd;
}

bool XmlDoc::Validate( DTDDocument * dtdDoc ) const
{
    return ( ( XmlElement * )root )->Validate( dtdDoc );
}

extern bool xmlparse(const char *, XmlDoc**); 
XmlDoc * XmlDoc::Parse (const string & filename)
{
	XmlDoc * xml;
	if (xmlparse(filename.c_str(), &xml))
		return xml;
	return NULL;
}

/* XmlAtt */

void XmlAtt::Display(int ident) const
{
    cout << " " << Name << " = \"" << Value << "\" "; 
}

/* XmlNode */

/* XmlElement */

XmlElement::XmlElement(const string name) : XmlNode(name) 
{
	nodeList.clear();
	iterator = nodeList.begin();
}

bool XmlElement::AddChild (XmlNode * newChild)
{
	if (newChild)
	{
		nodeList.push_back( newChild );
		return true;
	}
	return false;
}

XmlNode * XmlElement::FirstChild()
{
	iterator = nodeList.begin();
	return *iterator;
}

XmlNode * XmlElement::NextChild() 
{
	iterator++;
	if (iterator == nodeList.end())
		return NULL;
	return *iterator;
}

bool XmlElement::AddAttribute(XmlAtt * newAtt)
{
	if (newAtt)
	{
		attributeList.insert(Attribute(newAtt->Name, newAtt));
		return true;
	}
	return false;
}

const XmlAtt * XmlElement::GetAttribute (const string & attName) const
{
	return (attributeList.find(attName))->second;
}
		

ElementList * XmlElement::ElementChildren() const
{
    ElementList * elements = new ElementList();
    for (   vector <XmlNode*>::const_iterator it = nodeList.begin();
            it != nodeList.end();
            ++it )
     {
        if ( (*it)->IsElement() ) elements->push_back( (XmlElement*) *it );
     }

    return elements;
}

void XmlElement::Display(int ident) const
{
    // Opening
    cout << "<" << name;

    // Attributes
    AttributeList::const_iterator attIt;
    for ( attIt = attributeList.begin(); attIt != attributeList.end(); ++attIt )
		attIt->second->Display();
        
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

bool XmlElement::Validate( DTDDocument * dtdDoc ) const
{
#ifdef NDEBUG
    DTDElement const * matchingElem = dtdDoc->SearchForElem( name );

    if( matchingElem == NULL )
    {
        return false;
    }

    // First, we validate child elements' order within this element.
    bool result = matchingElem->ValidateElement( &nodeList );

    // Then, if all children are where we expect them to be, we go deeper
    // and try to validate every child.
    if( result )
    {
        NodeList::const_iterator nodeIt = nodeList.begin();

        while( result && ( nodeIt != nodeList.end() ) )
        {
            if( ( *nodeIt )->IsElement() )
            {
                result &= ( ( XmlElement * )( *nodeIt ) )->Validate( dtdDoc );
            }

            nodeIt++;
        }
    }

    return result;

#else
    return false;
#endif
}

/* XmlContent */

void XmlContent::Display(int ident) const
{
	cout << data;
}
