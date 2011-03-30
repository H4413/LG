/** DTD Interface */

#ifndef DTD_H
#define DTD_H

#include <vector>
#include <map>
#include <string>

/* Forward declarations */
class XmlNode;

/** 
 * Type declarations 
 * Mark is either *,?,+ or nothing
 **/
enum Mark
{
    NO_MARK,
    M_AST,
    M_PLUS,
    M_Q
};

/**
 * Type is the type of a contentspec
 **/
enum Type
{
    T_ANY,
    T_EMPTY,
    T_NAME,
    T_SEQ,
    T_CHOICE
};

/**********************************************************************
 * DTDContentspec is a pure virtual class which represents any 
 * content in an element.
 **********************************************************************/
class DTDContentspec 
{
    protected :
		Type contentSpec;

    public :
		DTDContentspec(Type type) : contentSpec(type) {}
		virtual void Display() const = 0;
		Type GetType() {return contentSpec;}
		virtual bool IsValidated( std::vector<XmlNode*>::const_iterator 
								* xmlNode, std::vector<XmlNode*> 
								const * nodeVector ) const = 0;
};

/**********************************************************************
 * DTDAttribute is an attribute in the DTD.
 **********************************************************************/
class DTDAttribute 
{
    private :
		std::string name;
		std::string type;
		std::string att;
      
    public:
		DTDAttribute(std::string name, std::string type = "CDATA",
					std::string att = "#IMPLIED") 
                    : name(name),type(type),att(att){};
		void Display() const;
};

/**********************************************************************
 * DTDAttList is a list of DTDAttribute.
 **********************************************************************/
class DTDAttList 
{
	protected:
		std::vector<DTDAttribute> attList;
		std::string name;
		
	public:
		DTDAttList () {}
		void Add (DTDAttribute * att);
		void SetName (std::string a_name) { name = a_name; }
		void Display() const;	
};

/**********************************************************************
 * DTDChildren is a pure virtual class which can be a DTDSequence, 
 * DTDChoice or DTDName.
 **********************************************************************/
class DTDChildren : public DTDContentspec 
{
	protected:
		Mark mark;
	
	public :
		DTDChildren(Type type) : DTDContentspec(type), mark(NO_MARK) {}
		virtual void Add(DTDChildren * child) {}
		virtual void AddList(std::vector<DTDChildren*>* list) {}
		virtual void AddMark(Mark a_mark) {mark = a_mark;}
		virtual void Display() const = 0;
		bool HasAMark() const {return mark != NO_MARK;}
};

/**********************************************************************
 * DTDSequence is a sequence which contains DTDChildren separated 
 * by commas.
 **********************************************************************/
class DTDSequence : public DTDChildren 
{
	protected :
		std::vector<DTDChildren*> seq;
		
	public :
		DTDSequence() : DTDChildren(T_SEQ) {}
		void Display() const;
		void Add(DTDChildren* child);
		void Add(std::string name);
		virtual void AddList(std::vector<DTDChildren*>* list);
		virtual bool IsValidated( std::vector<XmlNode*>::const_iterator 
								* xmlNode, std::vector<XmlNode*> 
								const * nodeVector ) const;
};

/**********************************************************************
 * DTDChoice is a choice which contains DTDChildren separated by pipes.
 **********************************************************************/
class DTDChoice : public DTDChildren 
{
    protected:
		std::vector<DTDChildren*> choice;
		
	public :
		DTDChoice() : DTDChildren(T_CHOICE) {}
		void Display() const;
		void Add(DTDChildren* child);
		void Add(std::string name);
		virtual void AddList(std::vector<DTDChildren*>* list);
		virtual bool IsValidated( std::vector<XmlNode*>::const_iterator 
								* xmlNode, std::vector<XmlNode*> 
								const * nodeVector ) const;	
};

/**********************************************************************
 * DTDName is a simple string contained in a DTDChildren.
 **********************************************************************/
class DTDName : public DTDChildren 
{
	private :
		std::string name;
		
	public :
		DTDName(std::string name) : DTDChildren(T_NAME), name(name) {};
		void Display() const;
		virtual bool IsValidated( std::vector<XmlNode*>::const_iterator 
								* xmlNode, std::vector<XmlNode*> 
								const * nodeVector ) const;
};

/**********************************************************************
 * DTDEmpty represents an empty DTDContentspec.
 **********************************************************************/
class DTDEmpty : public DTDContentspec 
{
	public :
		DTDEmpty() : DTDContentspec(T_EMPTY) {};
		void Display() const {}
		virtual bool IsValidated( std::vector<XmlNode*>::const_iterator 
								* xmlNode, std::vector<XmlNode*> 
								const * nodeVector ) const;
};

/**********************************************************************
 * DTDAny represents a DTDContentspec which can be anything.
 **********************************************************************/
class DTDAny : public DTDContentspec 
{
	public :
		DTDAny() : DTDContentspec(T_ANY) {};
		void Display() const {}
		virtual bool IsValidated( std::vector<XmlNode*>::const_iterator 
								* xmlNode, std::vector<XmlNode*> 
								const * nodeVector ) const;

};

/**********************************************************************
 * DTDElement is an element in a DTDDocument which contains 
 * DTDContentspec.
 **********************************************************************/
class DTDElement 
{
	private:
		std::string name;
		std::vector<DTDContentspec*> contentspec;
		
	public :
		DTDElement() {}
		DTDElement(std::string name) : name(name) {};
		void Display() const;
		void Add(DTDContentspec * content);
        bool ValidateElement( std::vector<XmlNode *> 
							const * xmlNodeVector ) const;
		std::string GetName() const { return name; }
};

/**********************************************************************
 * DTDDocument is the DTD main class, contains all the DTD : elements 
 * and attributes.
 **********************************************************************/
class DTDDocument 
{
	private :
		std::vector<DTDElement> elements;
		std::vector<DTDAttList> attList;
		std::string name;
		
	public :  
		DTDDocument() {}
		DTDDocument(std::string name) : name(name) {};
		void Display() const;
		void AddElement(DTDElement* element);
		void AddAttList(DTDAttList* attList); 
        DTDElement const * SearchForElem(std::string const & name)const;

		// static functions
		static DTDDocument * Parse(const std::string & filename);
};

#endif // DTD_H
