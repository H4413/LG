#include <fstream>
#include "XslTransform.h"

using namespace std;

bool XslTransform::SetOutputFile(const string filename)
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

bool XslTransform::Transform(const string xmlName, const string xslName)
{
	XmlDoc * xml, * xsl;
	if ( !((xml = XmlDoc::Parse(xmlName)) && (xsl = XmlDoc::Parse(xslName))) )
	{
		cerr << "Error parsing the files!" << endl;
		return false;
	}
	cout << "First constructor" << endl;
	return Transform(xml, xsl);
}

bool XslTransform::Transform(XmlDoc * xml, XmlDoc * xsl)
{
	xmlRoot = xml->GetRoot();
	xslRoot = xsl->GetRoot();
	currentNode = xmlRoot;
	cout << "Before first apply templates" << endl;
	applyTemplates();
	return false;
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
		
	if (currentNode->HasChild())
	{
		parents.push(currentNode);
		cout << "Current Node name" << currentNode->NodeName() << endl;
		currentNode = currentNode->FirstChild();
		cout << "Current Node name" << currentNode->NodeName() << endl;
		return true;
	}
		
	while (!parents.empty())
	{
		cout << "Parents not empty :" << parents.size() << endl;
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
	cout << "Search for templates" << endl;
	
	if (currentNode->IsContent())
		return NULL;
		
	XmlNode * xslChild = xslRoot->FirstChild();
	while (xslChild != NULL)
	{
		if (xslChild->HasAttributes())
		{
			cout << xslChild->GetAttribute("match")->Value
				<< " != " << currentNode->NodeName() << endl;
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
	cout << "Print templates" << endl;
	XmlNode * xslNode = templateNode->FirstChild();
	
	while (xslNode != NULL)
	{
		cout << "In while" << endl;
		
		if (xslNode->NodeName() == "apply-templates")
		{
			applyTemplates();
		}
		else if (xslNode->NodeName() == "value-of")
		{
			cout << "#### value of #########" << currentNode->NodeName() << endl;
			XmlNode * currentContent = currentNode->FirstChild();
			if (currentContent->IsContent())
				*out << ((XmlContent*)currentContent)->Content();
		}
		else if (xslNode->IsContent())
		{
			*out << ((XmlContent*)xslNode)->Content();
		} 
		else
		{
			cout << "Node : " << xslNode->NodeName() << endl;
			if (!xslNode->HasChild())
			{
				*out << "<" << xslNode->NodeName() << "/>" << endl;	
				xslNode = templateNode->NextChild();
				continue;	
			}
				
			begin(xslNode);
			printTemplate(xslNode);
			end(xslNode);
		}
		xslNode = templateNode->NextChild();	
	}
}
