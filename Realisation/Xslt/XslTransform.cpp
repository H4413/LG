#include <fstream>
#include "XslTransform.h"

bool XslTransform::setOutputFile(const string filename)
{
	cout << "changing output file" << endl;
	if (!filename.empty())
	{
		out = new ofstream();
		((ofstream*)out)->open(filename.c_str(), ios::out | ios::trunc);
		if (!((ofstream*)out)->is_open())
		{
			cout << "output is not opened" << endl;
			delete out;
			out = &cout;
			return false;
		}
		return true;
	}
	return false;
}

bool XslTransform::transform(const string xmlName, const string xslName)
{
	XmlDoc * xml, * xsl;
	if ( !((xml = XmlDoc::parse(xmlName)) && (xsl = XmlDoc::parse(xslName))) )
	{
		cerr << "Error parsing the files!" << endl;
		return false;
	}
	cout << "First constructor" << endl;
	return transform(xml, xsl);
}

bool XslTransform::transform(XmlDoc * xml, XmlDoc * xsl)
{
	xmlRoot = xml->getRoot();
	xslRoot = xsl->getRoot();
	currentNode = xmlRoot;
	cout << "Before first apply templates" << endl;
	applyTemplates();
	return false;
}

void XslTransform::begin(XmlNode * node)
{
    // Opening
    *out << "<" << node->nodeName();
    
    const AttributeList * attributeList = node->attributes();

    // Attributes
    AttributeList::const_iterator attIt;
    for ( attIt = attributeList->begin(); attIt != attributeList->end(); ++attIt )
		*out << " " << attIt->second->name << " = \"" << attIt->second->value << "\" "; 
        
    *out << ">" << endl;
}

void XslTransform::end(XmlNode * node)
{
	// Closing
    *out << "</" << node->nodeName() << ">" << endl;
}

void XslTransform::applyTemplates()
{
	static bool start = true;
	cout << "Apply templates" << endl;
	XmlNode * templateNode;	
	
	if (start)
		start = false;
	else
		nextNode();
	
	do {
		templateNode = searchForTemplate();
		if (templateNode)
			printTemplate(templateNode);
	} while(nextNode());
	
	cout << "End Apply templates" << endl;
}

bool XslTransform::nextNode()
{
	cout << "Next template" << endl;
	if (!currentNode)
		return false;
		
	if (currentNode->hasChild())
	{
		parents.push(currentNode);
		cout << "Current Node name" << currentNode->nodeName() << endl;
		currentNode = currentNode->firstChild();
		cout << "Current Node name" << currentNode->nodeName() << endl;
		return true;
	}
		
	while (!parents.empty())
	{
		cout << "Parents not empty :" << parents.size() << endl;
		currentNode = parents.top()->nextChild();
		
		if (currentNode)
			return true;
		
		parents.pop();
	}
	
	currentNode = NULL;
	return false;
}

XmlNode * XslTransform::searchForTemplate()
{
	cout << "Search for templates" << endl;
	
	if (currentNode->isContent())
		return NULL;
		
	XmlNode * xslChild = xslRoot->firstChild();
	while (xslChild != NULL)
	{
		if (xslChild->hasAttributes())
		{
			cout << xslChild->attribute("match")->value
				<< " != " << currentNode->nodeName() << endl;
			if (xslChild->attribute("match")->value == currentNode->nodeName())
				return xslChild;
			else if (xslChild->attribute("match")->value == "/"
					&& xmlRoot == currentNode)
				return xslChild;
		}
		xslChild = xslRoot->nextChild();
	}
	return NULL;
}

void XslTransform::printTemplate(XmlNode * templateNode)
{
	cout << "Print templates" << endl;
	XmlNode * xslNode = templateNode->firstChild();
	
	while (xslNode != NULL)
	{
		cout << "In while" << endl;
		
		if (xslNode->nodeName() == "apply-templates")
		{
			applyTemplates();
		}
		else if (xslNode->nodeName() == "value-of")
		{
			cout << "#### value of #########" << currentNode->nodeName() << endl;
			XmlNode * currentContent = currentNode->firstChild();
			if (currentContent->isContent())
				*out << ((XmlContent*)currentContent)->content();
		}
		else if (xslNode->isContent())
		{
			*out << ((XmlContent*)xslNode)->content();
		} 
		else
		{
			cout << "Node : " << xslNode->nodeName() << endl;
			if (!xslNode->hasChild())
			{
				*out << "<" << xslNode->nodeName() << "/>" << endl;	
				xslNode = templateNode->nextChild();
				continue;	
			}
				
			begin(xslNode);
			printTemplate(xslNode);
			end(xslNode);
		}
		xslNode = templateNode->nextChild();	
	}
}
