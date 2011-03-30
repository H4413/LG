#include <iostream>
#include <string>
#include <stack>


#include "Xml.h"

#ifndef XSLTRANSFORM_H
#define XSLTRANSFORM_H

class XslTransform
{
	protected:
		ostream * out;
		
	private:
		/* temporary attributes */
		XmlNode * xmlRoot;
		XmlNode * xslRoot;
		
		XmlNode * currentNode;
		stack<XmlNode*> parents;
		
	private:
		void begin(XmlNode * node);
		void end(XmlNode * node);
		
		bool nextNode();
		void applyTemplates();
		XmlNode * searchForTemplate();
		void printTemplate(XmlNode * templateNode);
	
	public:
		XslTransform() : out(&std::cout) { (parents.size() == 0 ? cout << "empty" << endl : cout << "full" << endl); }
		~XslTransform();
		
		bool setOutputFile(const string filename);
		
		bool transform(XmlDoc * xml, XmlDoc * xsl);
		bool transform(const string xmlName, const string xslName);
		
};

#endif /* XSLTRANSFORM_H */
