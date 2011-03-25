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
<<<<<<< HEAD
    public:
                vector<XmlNode*>   GetChildren() const { return nodeList; }
                vector<XmlElement*> GetChildrenElements() const;
                
                bool IsEmpty() { return nodeList.empty(); }

                void AddNode( XmlNode* n );  
                void AddElement( XmlElement* elt );  
                void AddContent( XmlContent* cont );  
                
                void AddAttribute( XmlAtt att );
                void AddAttribute( string n, string v );
                void SetAttList( vector<XmlAtt*>* aList )
                                        { attList = (*aList); }
                
        		void SetChildren( vector<XmlNode*>* children)
					{ nodeList = *children; }
                

                string GetName() const { return name; }
                XmlElement * GetNextElemChild( XmlElement * elem );

                // Override
                virtual bool isElement() { return true; }

                virtual void Display(int ident = 0) const;

                bool Validate( DTDDocument * dtdDoc ) const;

                // [Cons,Des]tructors 
                XmlElement( XmlElement * par, string n = "noname" )
                                    : XmlNode( par ), name( n ) {}
                ~XmlElement();

    private:
                string            name;
                vector<XmlAtt*>   attList;
                vector<XmlNode*>  nodeList;
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlContent : public XmlNode
{
<<<<<<< HEAD
    public:
                string GetContent() { return content; };
                
                vector<XmlElement*> GetChildrenElements() const {};

                // Override
                virtual bool isContent() { return true; };

                virtual void Display(int ident = 0) const;

                // [Cons,Des]tructors 
                XmlContent(XmlElement * par,  char * cont )
                                    : XmlNode( par ), content ( cont ) {};
    
    private:
                char * content;
=======
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

>>>>>>> 47eda987c772d3ead4cb22b80dfcd85a91e85efb
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlDoc
{
<<<<<<< HEAD
        
        public:
                XmlNode * GetRoot(){ return root; };
                
                void setRoot( XmlNode * nRoot ) { root = nRoot; };
                
                DTD * GetDTD() { return dtd; }

                void setDTD( DTD * dtd ) {this->dtd = dtd;}
                
                void Display() const;

                // [Cons,Des]tructors 
                XmlDoc( XmlNode * toor = NULL ) { root = toor; };
                ~XmlDoc() { delete root; delete dtd; }	

                bool Validate( DTDDocument * dtdDoc ) const;
        
        private: 
                XmlNode *  root;
                DTD * dtd;
=======
	public:
		// [Cons,Des]tructors 
		XmlDoc( XmlNode * toor = NULL ) { root = toor; dtd = NULL;};
		~XmlDoc();

		void setRoot( XmlNode * nRoot ) { root = nRoot; };
		XmlNode * getRoot(){ return root; };

		DTD * getDTD() { return dtd; }
		void setDTD( DTD * dtd ) {this->dtd = dtd;}

		void display() const;

	private: 
		XmlNode *  root;
		DTD * dtd;
>>>>>>> 47eda987c772d3ead4cb22b80dfcd85a91e85efb
};

#endif // XML_H
