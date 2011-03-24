/* Interface de la DTD */

#ifndef DTD_H
#define DTD_H

#include <vector>
#include <map>
#include <string>

/* Forward declarations */
class XmlNode;

/* This is NOT good, it shall be removed */
using namespace std;

/* Type declarations */
enum Mark
{
    NO_MARK,
    M_AST,
    M_PLUS,
    M_Q
};

enum Type
{
    T_ANY,
    T_EMPTY,
    T_NAME,
    T_SEQ,
    T_CHOICE
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDContentspec 
{
    protected :
                Type contentSpec;

    public :
                DTDContentspec(Type type) : contentSpec(type) {}

		virtual void display() const = 0;
                
                Type GetType() {return contentSpec;}

                virtual bool IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> * nodeVector ) const = 0;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDAttribute 
{
    private :
		string name;
		string type;
		string att;
      
    public:
		DTDAttribute(string name, string type = "CDATA",
                        string att = "#IMPLIED") : name(name),type(type),att(att){};
		void display() const;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDAttList 
{
	protected:
		vector<DTDAttribute> attList;
		string name;
		
	public:
		DTDAttList () {}
		void Add (DTDAttribute * att);
		void SetName (string a_name) { name = a_name; }
		void display() const;	
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDChildren : public DTDContentspec 
{
	protected:
		Mark mark;
	
	public :
		DTDChildren(Type type) : DTDContentspec(type), mark(NO_MARK) {}
		virtual void Add(DTDChildren * child) {}
		virtual void AddList(vector<DTDChildren*>* list) {}
		virtual void AddMark(Mark a_mark) {mark = a_mark;}
		virtual void display() const = 0;
		bool HasAMark() const {return mark != NO_MARK;}
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDSequence : public DTDChildren 
{
	public :
		DTDSequence() : DTDChildren(T_SEQ) {}
		void display() const;
		void Add(DTDChildren* child);
		void Add(string name);
		virtual void AddList(vector<DTDChildren*>* list);

                virtual bool IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> * nodeVector ) const;
		
	protected :
		vector<DTDChildren*> seq;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDChoice : public DTDChildren 
{
	public :
		DTDChoice() : DTDChildren(T_CHOICE) {}
		void display() const;
		void Add(DTDChildren* child);
		void Add(string name);
		virtual void AddList(vector<DTDChildren*>* list);

                virtual bool IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> * nodeVector ) const;

    protected:
		vector<DTDChildren*> choice;
	
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDName : public DTDChildren 
{
	public :
		DTDName(string name) : DTDChildren(T_NAME), name(name) {};
		void display() const;

                virtual bool IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> * nodeVector ) const;

	private :
		string name;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDEmpty : public DTDContentspec 
{
	public :
		DTDEmpty() : DTDContentspec(T_EMPTY) {};
		void display() const;

                virtual bool IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> * nodeVector ) const;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDAny : public DTDContentspec 
{
	public :
		DTDAny(string content) :
                    DTDContentspec(T_ANY), content(content){};
		void display() const;

                virtual bool IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> * nodeVector ) const;


	private : 
		string content;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDElement 
{
	public :
		DTDElement() {}
		DTDElement(string name) : name(name) {};
		void display() const;
		void Add(DTDContentspec * content);
                bool ValidateElement( vector<XmlNode *> * xmlNodeVector );
                
                string GetName() const { return name; }

	private:
		string name;
		vector<DTDContentspec*> contentspec;
};

/*****************************************************************************/
/*!
******************************************************************************/
class DTDDocument 
{
	public :  
		DTDDocument() {}
		DTDDocument(string name) : name(name) {};
		void display() const;
		void AddElement(DTDElement* element);
		void AddAttList(DTDAttList* attList); 
                
                DTDElement const * SearchForElem( string const & name ) const;

	private :
		vector<DTDElement> elements;
		vector<DTDAttList> attList;
		string name;
};

#endif // DTD_H
