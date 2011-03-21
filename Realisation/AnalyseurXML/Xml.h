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
                string name;
                
                void Display() const {};

                // [Cons,Des]tructors 
                DTD( string n = "" ) : name( n ) {};
};

/****************************************************************************/
/*!
*****************************************************************************/
class StyleSheet
{
    public:

                string filename;
                string type;
                
                void Display() const {};


                // [Cons,Des]tructors 
                StyleSheet( string f, string t )
                            : filename( f ), type( t ) {};
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
                XmlAtt( string n, string v ) : Name( n ), Value( v ){};
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlNode
{
    public:
                virtual bool isElement() { return false; };
                virtual bool isContent() { return false; };

                virtual void Display(int ident = 0) const = 0;

                //virtual bool ValidateNode(bool verbose) const;

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
                vector<XmlNode*>   GetChildren() { return nodeList; }

                void AddNode( XmlNode* n );  
                void AddElement( XmlElement* elt );  
                void AddContent( XmlContent* cont );  
                
                void AddAttribute( XmlAtt att );
                void AddAttribute( string n, string v );
                void SetAttList( vector<XmlAtt*>* aList )
                                        { attList = (*aList); }
				void SetChildren( vector<XmlNode*>* children)
										{nodeList = *children; }

                // Override
                virtual bool isElement() { return true; }

                virtual void Display(int ident = 0) const;

                //virtual bool ValidateNode(bool verbose) const;

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
    public:
                string GetContent() { return content; };
                
                // Override
                virtual bool isContent() { return true; };

                virtual void Display(int ident = 0) const;

                //virtual bool ValidateNode(bool verbose) const;

                // [Cons,Des]tructors 
                XmlContent(XmlElement * par,  char * cont )
                                    : XmlNode( par ), content ( cont ) {};
    
    private:
                char * content;
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlDoc
{
        
        public:
                XmlNode * GetRoot(){ return root; };
                
                void setRoot( XmlNode * nRoot ) { root = nRoot; };
                
                DTD * GetDTD() { return dtd; }

                void setDTD( DTD * dtd ) {this->dtd = dtd;}
                
                bool ValidateDocument(bool verbose) const;  
                
                void Display() const;

                // [Cons,Des]tructors 
                XmlDoc( XmlNode * root = NULL ) {};
                ~XmlDoc() { delete root; delete dtd; }	
        
        private: 
                XmlNode *  root;
                DTD * dtd;
                
                     
};

#endif // XML_H
