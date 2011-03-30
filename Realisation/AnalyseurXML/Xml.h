/** Xml Interface */

#ifndef XML_H
#define XML_H

#include <string>
#include <vector>
#include <map>

//using namespace std;

/* Forward declarations */
class DTDDocument;
class XmlNode;
class XmlElement;
class XmlContent;
class XmlAtt;

/**
 * Type is the type of a contentspec
 **/
typedef enum
{
    XmlElementNode,
    XmlAttributeNode,
    XmlContentNode,
    XmlNullNode
} NodeType;

/* Helper types defenitions */
typedef std::vector<XmlNode*>                NodeList;
typedef std::vector <XmlNode*>::iterator     NodeIterator;
typedef std::vector<XmlElement*>             ElementList;
typedef std::map<std::string,XmlAtt*>        AttributeList;
typedef std::pair<std::string,XmlAtt*>       Attribute;

/**********************************************************************
 * This class holds the DTD information contained in the XML file
 **********************************************************************/
class DTD
{
    public:
        std::string FileName;
        std::string Name;

        // [Cons,Des]tructors 
        DTD( std::string n = "", std::string fn = "" )
                            : Name( n ), FileName( fn ) {};
                            
        void Display() const;
};

/**********************************************************************
 * This class holds the StyleSheet information contained in the XML file
 * @warning This class wasn't well implemented
 **********************************************************************/
class StyleSheet
{
    public:
        std::string FileName;
        std::string styleType;

        // [Cons,Des]tructors 
        StyleSheet( std::string f, std::string t )
                    : FileName( f ), styleType( t ) {};
                            
        void Display() const {};
};

/**********************************************************************
 * This class implements a XML attribute
 **********************************************************************/
class XmlAtt
{
    public:
        std::string Name;
        std::string Value;
        
        // [Cons,Des]tructors 
        XmlAtt(std::string n, std::string v) : Name( n ), Value( v ){}
        
        virtual void Display(int ident = 0) const;
};

/**********************************************************************
 * This is the abstract class for the XML nodes in the XML Tree
 * structure
 **********************************************************************/
class XmlNode
{
    protected:
        std::string name;
        
    public:
        // [Cons,Des]tructors 
        XmlNode(const std::string name = "noname") : name(name) {}
        ~XmlNode() {}
                
        virtual bool IsElement() const { return false; }
        virtual bool IsContent() const { return false; }
        virtual NodeType GetNodeType() const { return XmlNullNode; }
        
        virtual bool AddAttribute(XmlAtt * newAtt) {return false;}
        virtual bool HasAttributes() const { return false; }
        virtual const AttributeList * Attributes() const {return NULL;}
        virtual const XmlAtt * GetAttribute 
					(const std::string & attName) const {return NULL;}
        
        virtual bool AddChild (XmlNode * newChild) {return false;}
        virtual bool HasChild() const { return false; }
        virtual XmlNode * FirstChild() { return NULL; }
        virtual XmlNode * NextChild() { return NULL; }
        virtual const NodeList * Children() const { return NULL; }
        
        virtual void SetNodeName 
					(const std::string nodeName) { name = nodeName; }
        virtual const std::string NodeName () const { return name; }
                
        virtual void Display(int ident = 0) const = 0;

};

/**********************************************************************
 * This class implements a XML element
 * It's a node in the XML Tree structure
 **********************************************************************/
class XmlElement : public XmlNode
{
    private:
        NodeIterator iterator;
                
    protected:
        AttributeList   attributeList;
        NodeList        nodeList;
                
    public:
        // [Cons,Des]tructors 
        XmlElement(const std::string name);
        ~XmlElement();        
        
        virtual bool AddAttribute(XmlAtt * newAtt);
        virtual bool HasAttributes() const 
									{ return attributeList.size() > 0; }
        void SetAttributsList(AttributeList * list) 
									{ attributeList = *list; } 
        virtual const AttributeList * Attributes() const 
									{ return &attributeList; }
        virtual const XmlAtt * GetAttribute (const std::string & attName) const;
        
        virtual bool AddChild (XmlNode * newChild);
        virtual bool HasChild() const { return nodeList.size() > 0; }
        virtual XmlNode * FirstChild();
        virtual XmlNode * NextChild();
        void SetChildren (NodeList * children) { nodeList = *children; }
        virtual const NodeList * Children() const { return &nodeList; }
        ElementList * ElementChildren() const;
        
        bool Validate( DTDDocument * dtdDoc ) const;
        
        // Override
        virtual bool IsElement() const { return true; };
        virtual NodeType GetNodeType() const { return XmlElementNode; }
        virtual void Display(int ident = 0) const;
};

/**********************************************************************
 * This class implements a PCDATA element
 * It's a node in the XML Tree structure
 **********************************************************************/
class XmlContent : public XmlNode
{
    private:
        std::string data;
        
    public:
        // [Cons,Des]tructors 
        XmlContent(const std::string data )
                    : XmlNode("xmlContent"), data ( data ) {}
                    
        const std::string & Content() const { return data; }
        void SetContent (const std::string cont) { data = cont; }
        const unsigned int Size () const { return data.size(); }
        
        // Override
        virtual bool IsContent() const { return true; };
        virtual NodeType GetNodeType() const { return XmlContentNode; }
        virtual void Display(int ident = 0) const;

};

/**********************************************************************
 * This class implements a XML document
 **********************************************************************/
class XmlDoc
{
    private: 
        XmlNode *  root;
        DTD * dtd;
        
    public:
        // [Cons,Des]tructors 
        XmlDoc( XmlNode * toor = NULL ) { root = toor; dtd = NULL;};
        ~XmlDoc();

        void SetRoot( XmlNode * nRoot ) { root = nRoot; };
        XmlNode * GetRoot(){ return root; };

        DTD * GetDTD() { return dtd; }
        void SetDTD( DTD * dtd ) {this->dtd = dtd;}

        void Display() const;
        
        bool Validate( DTDDocument * dtdDoc ) const;

        // static functions
        static XmlDoc * Parse(const std::string & filename);
};

#endif // XML_H
