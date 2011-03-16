/* Xml.h */

#ifndef XML_H
#define XML_H

#include <vector>

using namespace std;

/* Classes */

class XmlDoc
{
	string DocName;
	
	XmlDoc *Root;  
	
	
	XmlDoc(){Root= NULL;};
	
	
	XmlDoc *GetRoot(){return Root ;}
	XmlDoc *SetRoot(){ ;}
	

};

class XmlAtt
{
    public:
            String Name;
            String Value;
};

class XmlNode
{

};

class XmlElement : XmlNode
{
    private:
                Vector<XmlAtt>   attList;
                Vector<XmlNode>  nodeList;
                XmlElement         * parent;
                
    public:
                XmlElement          * GetParent()   { return parent };
                Vector<XmlNode>   GetChildren() { return nodeList };

                XmlElement();
                XmlElement( XmlElement parElement );
                ~XmlElement();
};

class XmlCont : XmlNode
{
    private:
                String content;
    public:
                String GetContent()     { return content };
                
                XmlNode();
                XmlNode( String cont )  { content = cont };
};

#endif // XML_H
