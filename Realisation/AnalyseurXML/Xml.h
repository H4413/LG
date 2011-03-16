/* Xml.h */

/*TODO
*   Display
*/


#ifndef XML_H
#define XML_H

#include <string>

using namespace std;

class XmlNode;
class XmlElement;
class XmlContent;

/* Classes */

class XmlDoc
{
	string DocName;
	
	XmlDoc *Root;  
	
	
	XmlDoc(){Root= NULL;};
	
	
	XmlDoc *GetRoot(){ return Root; }

};

class XmlAtt
{
    public:
            string Name;
            string Value;

            // [Cons,Des]tructors 
            XmlAtt( string n, String v ) : Name( n ), Value( v );
};

class XmlNode
{
    public:
                virtual bool isElement();
                virtual bool isContent();
                
                XmlElement * GetParent()   { return parent; };

                // [Cons,Des]tructors 
                XmlNode( XmlElement * par = null ) : parent( par );

    protected:
                XmlElement * parent;

};

class XmlElement : XmlNode
{
    public:
                vector<XmlNode>   GetChildren() { return nodeList; };

                void AddNode( XmlNode node );  
                void AddAttribute( XmlAtt att );
                void AddAttribute( string n, String v );
                
                // Override
                bool isElement() { return true; };
                bool isContent() { return false; };

                // [Cons,Des]tructors 
                XmlElement();
                ~XmlElement();
    
    private:
                vector<XmlAtt>   attList;
                vector<XmlNode>  nodeList;
                
};

class XmlContent : XmlNode
{
    public:
                string GetContent() { return content; };
                
                // Override
                bool isElement() { return false; };
                bool isContent() { return true; };

                // [Cons,Des]tructors 
                XmlContent( string cont ) : content ( cont );
    
    private:
                string content;
};

#endif // XML_H
