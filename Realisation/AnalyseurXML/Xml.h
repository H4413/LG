/* Xml.h */

#ifndef XML_H
#define XML_H

#include <vector>

using namespace std;

/* Classes */

class XmlAtt
{
    public:
            String Name;
            String Value;
};

class XmlNode
{

};

class XmlElt : XmlNode
{
    private:
                Vector<XmlAtt>   attList;
                Vector<XmlNode>  nodeList;
                XmlElt         * parent;
                
    public:
                XmlElt          * GetParent()   { return parent };
                Vector<XmlNode>   GetChildren() { return nodeList };

                XmlElt();
                XmlElt( XmlElt parElt );
                ~XmlElt();
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
