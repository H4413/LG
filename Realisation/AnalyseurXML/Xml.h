/* Xml.h */

/*TODO
 *   Display
 *   Validation du document XML
 */


#ifndef XML_H
#define XML_H

#include <string>
#include <vector>

class DTDDocument;

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
                char * name;
                
                void Display() const {};

                // [Cons,Des]tructors 
                DTD( char * n = "" ) : name( n ) {};
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

                XmlElement * GetParent()   { return parent; };
    
                virtual vector<XmlElement*> GetChildrenElements() const = 0;

                // [Cons,Des]tructors 
                XmlNode( XmlElement * par = NULL ) :
                        parent( par ) {};

    protected:
                XmlElement * parent;
};

/****************************************************************************/
/*!
*****************************************************************************/
class XmlElement : public XmlNode
{
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
                

                string GetName() { return name; }
                XmlElement * GetNextElemChild( XmlElement * elem );

                // Override
                virtual bool isElement() { return true; }

                virtual void Display(int ident = 0) const;

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
                
                vector<XmlElement*> GetChildrenElements() const {};
                // Override
                virtual bool isContent() { return true; };

                virtual void Display(int ident = 0) const;

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
                
                void Display() const;

                // [Cons,Des]tructors 
                XmlDoc( XmlNode * root = NULL ) {};
                ~XmlDoc() { delete root; delete dtd; }	
        
        private: 
                XmlNode *  root;
                DTD * dtd;
                
                     
};

#endif // XML_H
