/* Xml.cpp */

/* Project includes */
#include "Xml.h"
#include "DTD.h"

/* System includes */
#include <string.h>
#include <iostream>

/* DTD */

void DTD::display() const
{
    cout << "<!DOCTYPE " << name;
    cout << " SYSTEM" << " \"" << fileName << "\">" << endl;
}

/* XmlDoc */

void XmlDoc::display() const
{
    cout << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
    if (dtd)
		dtd->display();
	if (root)
		root->display();
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

/* XmlAtt */

void XmlAtt::display(int ident) const
{
    cout << " " << name << " = \"" << value << "\" "; 
}

/* XmlNode */

/* XmlElement */

XmlElement::XmlElement(const string name) : XmlNode(name) 
{
	nodeList.clear();
	iterator = nodeList.begin();
}

bool XmlElement::addChild (XmlNode * newChild)
{
	if (newChild)
	{
		nodeList.push_back( newChild );
		return true;
	}
	return false;
}

XmlNode * XmlElement::firstChild()
{
	iterator = nodeList.begin();
	return *iterator;
}

XmlNode * XmlElement::nextChild() 
{
	iterator++;
	if (iterator == nodeList.end())
		return NULL;
	return *iterator;
}

bool XmlElement::addAttribute(XmlAtt * newAtt)
{
	if (newAtt)
	{
		attributeList.insert(Attribute(newAtt->name, newAtt));
		return true;
	}
	return false;
}

const XmlAtt * XmlElement::attribute (const string & attName) const
{
	return (attributeList.find(attName))->second;
}
		

ElementList * XmlElement::elementChildren() const
{
    ElementList * elements = new ElementList();
    for (   vector <XmlNode*>::const_iterator it = nodeList.begin();
            it != nodeList.end();
            ++it )
     {
        if ( (*it)->isElement() ) elements->push_back( (XmlElement*) *it );
     }

    return elements;
}

void XmlElement::display(int ident) const
{
    // Opening
    cout << "<" << name;

    // Attributes
    AttributeList::const_iterator attIt;
    for ( attIt = attributeList.begin(); attIt != attributeList.end(); ++attIt )
		attIt->second->display();
        
    cout << ">" << endl;
    
    // Elements and content
    vector <XmlNode*>::const_iterator nIt;
    for ( nIt = nodeList.begin(); nIt != nodeList.end(); ++nIt )
    {
		for (int i = 0; i <= ident; i++) cout << "\t";
        (*nIt)->display(ident+1);	
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
            if( ( *nodeIt )->isElement() )
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

void XmlContent::display(int ident) const
{
	cout << data;
}
