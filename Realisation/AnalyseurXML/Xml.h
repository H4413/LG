/* Xml.h */

/*TODO
 *   display
 *   Validation du document XML
 */


#ifndef XML_H
#define XML_H

#include <string>
#include <vector>
#include <map>

class DTDDocument;

using namespace std;

class XmlNode;
class XmlElement;
class XmlContent;
class XmlAtt;

typedef enum
{
	XmlElementNode,
	XmlAttributeNode,
	XmlContentNode,
	XmlNullNode
} NodeType;

typedef vector<XmlNode*> 				NodeList;
typedef vector <XmlNode*>::iterator		NodeIterator;
typedef vector<XmlElement*> 			ElementList;
typedef map<string,XmlAtt*>				AttributeList;
typedef pair<string,XmlAtt*>			Attribute;

/* Classes */

/****************************************************************************/
/*!
*****************************************************************************/
class DTD
{
    public:
		string fileName;
		string name;

		// [Cons,Des]tructors 
		DTD( string n = "", string fn = "" )
							: name( n ), fileName( fn ) {};
							
		void display() const;
};

/****************************************************************************/
/*!
*****************************************************************************/
class StyleSheet
{
    public:
		string filename;
		string type;

		// [Cons,Des]tructors 
		StyleSheet( string f, string t )
					: filename( f ), type( t ) {};
							
		void display() const {};
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlAtt
{
    public:
		string name;
		string value;
		
		// [Cons,Des]tructors 
		XmlAtt( string n, string v ) : name( n ), value( v ){};
		
		virtual void display(int ident = 0) const;
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlNode
{
	protected:
		string name;
		
	public:
		// [Cons,Des]tructors 
		XmlNode(const string name = "noname") : name(name) {}
		~XmlNode() {}
				
		virtual bool isElement() const { return false; }
		virtual bool isContent() const { return false; }
		virtual NodeType nodeType() const { return XmlNullNode; }
		
		virtual bool addAttribute(XmlAtt * newAtt) {return false;}
		virtual bool hasAttributes() const { return false; }
		virtual const AttributeList * attributes() const { return NULL; }
		virtual const XmlAtt * attribute (const string & attName) const {return NULL;}
		
		virtual bool addChild (XmlNode * newChild) {return false;}
		virtual bool hasChild() const { return false; }
		virtual XmlNode * firstChild() { return NULL; }
		virtual XmlNode * nextChild() { return NULL; }
		virtual const NodeList * children() const { return NULL; }
		
		virtual void setNodeName (const string nodeName) { name = nodeName; }
		virtual const string nodeName () const { return name; }
				
		virtual void display(int ident = 0) const = 0;

};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlElement : public XmlNode
{
	private:
		NodeIterator iterator;
				
	protected:
		AttributeList	attributeList;
		NodeList		nodeList;
				
	public:
		// [Cons,Des]tructors 
		XmlElement(const string name);
		~XmlElement();		
		
		virtual bool addAttribute(XmlAtt * newAtt);
		virtual bool hasAttributes() const { attributeList.size() > 0; }
		void setAttributsList(AttributeList * list) { attributeList = *list; } 
		virtual const AttributeList * attributes() const { return &attributeList; }
		virtual const XmlAtt * attribute (const string & attName) const;
		
		virtual bool addChild (XmlNode * newChild);
		virtual bool hasChild() const { nodeList.size() > 0; }
		virtual XmlNode * firstChild();
		virtual XmlNode * nextChild();
		void setChildren (NodeList * children) { nodeList = *children; }
		virtual const NodeList * children() const { return &nodeList; }
		ElementList * elementChildren() const;
		
		bool Validate( DTDDocument * dtdDoc ) const;
		
		// Override
		virtual bool isElement() const { return true; };
		virtual NodeType nodeType() const { return XmlElementNode; }
		virtual void display(int ident = 0) const;
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlContent : public XmlNode
{
	private:
		string data;
		
	public:
		// [Cons,Des]tructors 
		XmlContent(const string data )
					: XmlNode("xmlContent"), data ( data ) {}
					
		const string & content() const { return data; }
		void setContent (const string cont) { data = cont; }
		const unsigned int size () const { return data.size(); }
		
		// Override
		virtual bool isContent() const { return true; };
		virtual NodeType nodeType() const { return XmlContentNode; }
		virtual void display(int ident = 0) const;

};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlDoc
{
	public:
		// [Cons,Des]tructors 
		XmlDoc( XmlNode * toor = NULL ) { root = toor; dtd = NULL;};
		~XmlDoc();

		void setRoot( XmlNode * nRoot ) { root = nRoot; };
		XmlNode * getRoot(){ return root; };

		DTD * getDTD() { return dtd; }
		void setDTD( DTD * dtd ) {this->dtd = dtd;}

		void display() const;
		
		bool Validate( DTDDocument * dtdDoc ) const;

	private: 
		XmlNode *  root;
		DTD * dtd;
};

#endif // XML_H
