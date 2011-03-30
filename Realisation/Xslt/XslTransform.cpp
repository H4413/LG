#include <fstream>
#include "XslTransform.h"

using namespace std;

bool XslTransform::SetOutputFile(const string filename)
{
	if (!filename.empty())
	{
		out = new ofstream();
		((ofstream*)out)->open(filename.c_str(), ios::out | ios::trunc);
		if (!((ofstream*)out)->is_open())
		{
			delete out;
			out = &cout;
			return false;
		}
		return true;
	}
	return false;
}

bool XslTransform::Transform(const string xmlName, const string xslName)
{
	XmlDoc * xml, * xsl;
	if ( !(xml = XmlDoc::Parse(xmlName)) )
	{
		cerr << "Error parsing XML file!" << endl;
		return false;
	}

	if ( !(xsl = XmlDoc::Parse(xslName)) )
	{
		cerr << "Error parsing XSL file!" << endl;
		return false;
	}
	
	return Transform(xml, xsl);
}

bool XslTransform::Transform(XmlDoc * xml, XmlDoc * xsl)
{
	xmlRoot = xml->GetRoot();
	xslRoot = xsl->GetRoot();
	currentNode = xmlRoot;
	applyTemplates(true);
	
	cout << "Html generated!" << endl;
	return true;
}

void XslTransform::begin(XmlNode * node)
{
    // Opening
    *out << "<" << node->NodeName();
    
    const AttributeList * attributeList = node->Attributes();

    // Attributes
    AttributeList::const_iterator attIt;
    for ( attIt = attributeList->begin(); attIt != attributeList->end(); ++attIt )
		*out << " " << attIt->second->Name << " = \"" << attIt->second->Value << "\" "; 
        
    *out << ">" << endl;
}

void XslTransform::end(XmlNode * node)
{
	// Closing
    *out << "</" << node->NodeName() << ">" << endl;
}

void XslTransform::applyTemplates(bool isRoot)
{
	XmlNode * templateNode;	

	if (!isRoot)
		nextNode();
	
	do {
		templateNode = searchForTemplate();
		if (templateNode)
			printTemplate(templateNode);
	} while(nextNode());
}

bool XslTransform::nextNode()
{
	if (!currentNode)
		return false;
		
	if (currentNode->HasChild())
	{
		parents.push(currentNode);
		currentNode = currentNode->FirstChild();
		return true;
	}
		
	while (!parents.empty())
	{
		currentNode = parents.top()->NextChild();
		
		if (currentNode)
			return true;
		
		parents.pop();
	}
	
	currentNode = NULL;
	return false;
}

XmlNode * XslTransform::searchForTemplate()
{	
	if (currentNode->IsContent())
		return NULL;
		
	XmlNode * xslChild = xslRoot->FirstChild();
	while (xslChild != NULL)
	{
		if (xslChild->HasAttributes())
		{
			if (xslChild->GetAttribute("match")->Value == currentNode->NodeName())
				return xslChild;
			else if (xslChild->GetAttribute("match")->Value == "/"
					&& xmlRoot == currentNode)
				return xslChild;
		}
		xslChild = xslRoot->NextChild();
	}
	return NULL;
}

void XslTransform::printTemplate(XmlNode * templateNode)
{
	XmlNode * xslNode = templateNode->FirstChild();
	
	while (xslNode != NULL)
	{		
		if (xslNode->NodeName() == "apply-templates")
		{
			applyTemplates();
		}
		else if (xslNode->NodeName() == "value-of")
		{
			valueOf(currentNode);
		}
		else if (xslNode->IsContent())
		{
			*out << ((XmlContent*)xslNode)->Content();
		} 
		else
		{
			if (!xslNode->HasChild())
			{
				*out << "<" << xslNode->NodeName() << "/>" << endl;	
			} else {
				begin(xslNode);
				printTemplate(xslNode);
				end(xslNode);			
			}
		}
		xslNode = templateNode->NextChild();	
	}
}

void XslTransform::valueOf(XmlNode * node)
{
	if (node->IsContent())
		*out << " " << ((XmlContent*)node)->Content();
	
	if (node->HasChild())
	{
		NodeList::const_iterator it;
		for ( it = node->Children()->begin(); 
				it != node->Children()->end(); ++it )
		{
			valueOf(*it);
		}
	}
}
