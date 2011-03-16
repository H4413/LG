/* Xml.h */

/*TODO
*   Display
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

class XmlAtt
{
    public:
            string Name;
            string Value;
                
            void Display() const;

            // [Cons,Des]tructors 
            XmlAtt( string n, string v );
};

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
