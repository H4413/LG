/* Xml.h */

#ifndef XML_H
#define XML_H

#include <Vector>
#include <String>
using namespace std;

/* Classes */

class XmlDoc
{
	string DocName;
	
	XmlDoc *Root;  
	
	
	XmlDoc(){Root= NULL;};
	
	
	XmlDoc *GetRoot(){ return Root; }
	XmlDoc *SetRoot(){ ;}
	

};

class XmlAtt
{
    public:
            String Name;
            String Value;


            // [Cons,Des]tructors 
            XmlAtt( String n, String v ) { Name = n; Value = v };
};

class XmlNode
{
    protected:
                XmlElement * parent;

    public:
                virtual bool isElement();
                virtual bool isContent();

                // [Cons,Des]tructors 
                XmlNode() { parent = null };
                XmlNode( XmlElement * parElement ) { parent = parElement; };

};

class XmlElement : XmlNode
{
    private:
                Vector<XmlAtt>   attList;
                Vector<XmlNode>  nodeList;
                
    public:
                XmlElement      * GetParent()   { return parent; };
                Vector<XmlNode>   GetChildren() { return nodeList; };

                // Override
                bool isElement() { return true; };
                bool isContent() { return false; };

                // [Cons,Des]tructors 
                XmlElement();
                ~XmlElement();
};

class XmlContent : XmlNode
{
    private:
                String content;
    public:
                String GetContent()     { return content; };
                
                // Override
                bool isElement() { return false; };
                bool isContent() { return true; };

                // [Cons,Des]tructors 
                XmlContent();
                XmlContent( String cont )  { content = cont; };
};

#endif // XML_H
