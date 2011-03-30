#ifndef XSLTRANSFORM_H
#define XSLTRANSFORM_H

#include <iostream>
#include <string>
#include <stack>

#include "Xml.h"

/**********************************************************************
 * XslTransformation is a class implementation of a tranformation
 * algorithm XML to HTML, using a XSL file
 **********************************************************************/
class XslTransform
{
	protected:
		std::ostream * out;
		
	private:
		/* temporary attributes */
		XmlNode * xmlRoot;
		XmlNode * xslRoot;
		XmlNode * currentNode;
		std::stack<XmlNode*> parents;
		
	private:
		void begin(XmlNode * node);
		void end(XmlNode * node);
		
		bool nextNode();
		void applyTemplates(bool isRoot = false);
		void valueOf(XmlNode * node);
		
		XmlNode * searchForTemplate();
		void printTemplate(XmlNode * templateNode);
	
	public:
		XslTransform() : out(&std::cout) {}
		~XslTransform();
		
		bool SetOutputFile(const std::string filename);
		
		bool Transform(XmlDoc * xml, XmlDoc * xsl);
		bool Transform(const std::string xmlName, 
						const std::string xslName);
		
};

#endif /* XSLTRANSFORM_H */
