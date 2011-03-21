/* Xml.h */

/*TODO
 *   Display
 *   Validation du document XML
 */


#ifndef XML_H
#define XML_H

#include <string>
#include <vector>

using namespace std;

class XmlNode;
class XmlElement;
class XmlContent;

/* Classes */

/****************************************************************************/
/*!
*****************************************************************************/
class DTD
{
    public:
		//string filename;
		string dtdname;
		
		
		void Display() const;

		DTD(string name);
		string& name(){return dtdname;}
}

/****************************************************************************/
/*!
*****************************************************************************/
class StyleSheet
{
    public:

		string filename;
		string type;
		
		void dis() const;
}

/****************************************************************************/
/*!
*****************************************************************************/
class XmlDoc
{
	
	public: 
		//string DocName;
		
		XmlElement&  XmlElement;
		DTD& dtd;
		
		//XmlDoc doc = new XmlDoc();
		
		
		XmlDoc(){root= NULL;};
		
		XmlElement& root(){return XmlElement;}
		void setroot(XmlElement& root);
		
		DTD& dtd(){return dtd;}
		void setDTD(DTD& dtd);
		
		//void AddElement();
		//void AddStyleSheet();
		//void AddDTD();
		
		
		//XmlDoc *Getroot(){ return root; }
	
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlAtt
{
    public:
		string Name;
		string Value;
		
		void Display() const;
		
		// [Cons,Des]tructors 
		XmlAtt( string n, String v ) : Name( n ), Value( v );
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlNode
{
    public:
            virtual bool isElement() = 0;
            virtual bool isContent() = 0;

            virtual void Display() const = 0;

            XmlElement * GetParent()   { return parent; };

            // [Cons,Des]tructors 
            XmlNode( XmlElement * par = NULL ) : parent( par ){};

    protected:
            XmlElement * parent;
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlElement : XmlNode
{
    public:
            vector<XmlNode>   GetChildren() { return nodeList; };

            void AddElement( XmlElement element );  
            void AddContent( string cont );  
            void AddAttribute( XmlAtt att );
            void AddAttribute( string n, String v );

            // Override
            virtual bool isElement() { return true; };
            virtual bool isContent() { return false; };

            virtual void Display() const;

            // [Cons,Des]tructors 
            XmlElement( string n = "noname" ) : name( n );
            ~XmlElement();

    private:
            string           name;
            vector<XmlAtt>   attList;
            vector<XmlNode>  nodeList;

};

class XmlContent : XmlNode
{
public:
string GetContent() { return content; };

// Override
virtual bool isElement() { return false; };
virtual bool isContent() { return true; };

virtual void Display() const;

// [Cons,Des]tructors 
XmlContent( string cont ) : content ( cont );

private:
string content;
};

/****************************************************************************/
/*!
*****************************************************************************/

class XmlNode
{
    public:
                virtual bool isElement() = 0;
                virtual bool isContent() = 0;

                virtual void Display() const = 0;
                
                XmlElement * GetParent()   { return parent; };

                // [Cons,Des]tructors 
                XmlNode( XmlElement * par = NULL ) : parent( par ){};

    protected:
                XmlElement * parent;

};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlElement : public XmlNode
{
    public:
                vector<XmlNode>   GetChildren() { return nodeList; };

                void AddElement( XmlElement elt  );  
                void AddContent( XmlContent cont );  
                void AddAttribute( XmlAtt att );
                void AddAttribute( string n, string v );
                
                // Override
                virtual bool isElement() { return true; };
                virtual bool isContent() { return false; };

                virtual void Display() const;

                // [Cons,Des]tructors 
                XmlElement( string n = "noname" ) : name( n ) {};
                ~XmlElement();
    
    private:
                string           name;
                vector<XmlAtt>   attList;
                vector<XmlNode>  nodeList;
                
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlContent : public XmlNode
{
    public:
                string GetContent() { return content; };
                
                // Override
                virtual bool isElement() { return false; };
                virtual bool isContent() { return true; };

                virtual void Display() const;

                // [Cons,Des]tructors 
                XmlContent( string cont ) : content ( cont ) {};
    
    private:
                string content;
};

#endif // XML_H
