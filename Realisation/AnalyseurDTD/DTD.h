/* Interface de la DTD */

#include <vector>
#include <map>
#include <string>

using namespace std;

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

class DTDContentspec 
{
    protected :
                Type contentSpec;

    public :
                DTDContentspec(Type type) : contentSpec(type) {}

		virtual void Display() const = 0;
                
                Type GetType() {return contentSpec;}
};

class DTDAttribute 
{
    private :
		string name;
		string type;
		string att;
      
    public:
		DTDAttribute(string name, string type = "CDATA", string att = "#IMPLIED") : name(name),type(type),att(att){};
		void Display() const;
};

class DTDAttList 
{
	protected:
		vector<DTDAttribute> attList;
		string name;
		
	public:
		DTDAttList () {}
		void Add (DTDAttribute * att);
		void SetName (string a_name) { name = a_name; }
		void Display() const;	
};

class DTDChildren : public DTDContentspec 
{
	protected:
		Mark mark;
	
	public :
		DTDChildren(Type type) : DTDContentspec(type), mark(NO_MARK) {}
		virtual void Add(DTDChildren * child) {}
		virtual void AddList(vector<DTDChildren*>* list) {}
		virtual void AddMark(Mark a_mark) {mark = a_mark;}
		virtual void Display() const = 0;
		bool HasAMark() const {return mark != NO_MARK;}
};

class DTDSequence : public DTDChildren 
{
	public :
		DTDSequence() : DTDChildren(T_SEQ) {}
		void Display() const;
		void Add(DTDChildren* child);
		void Add(string name);
		virtual void AddList(vector<DTDChildren*>* list);
		
	protected :
		vector<DTDChildren*> seq;
};

class DTDChoice : public DTDChildren 
{
	public :
		DTDChoice() : DTDChildren(T_CHOICE) {}
		void Display() const;
		void Add(DTDChildren* child);
		void Add(string name);
		virtual void AddList(vector<DTDChildren*>* list);

    protected:
		vector<DTDChildren*> choice;
	
};

class DTDName : public DTDChildren 
{
	public :
		DTDName(string name) : DTDChildren(T_NAME), name(name) {};
		void Display() const;

	private :
		string name;
};

class DTDEmpty : public DTDContentspec 
{
	public :
		DTDEmpty() : DTDContentspec(T_EMPTY) {};
		void Display() const;
};

class DTDAny : public DTDContentspec 
{
	public :
		DTDAny(string content) : DTDContentspec(T_ANY), content(content){};
		void Display() const;

	private : 
		string content;
};

class DTDElement 
{
	public :
		DTDElement() {}
		DTDElement(string name) : name(name) {};
		void Display() const;
		void Add(DTDContentspec * content);

	private:
		string name;
		vector<DTDContentspec*> contentspec;
};

class DTDDocument 
{
	public :  
		DTDDocument() {}
		DTDDocument(string name) : name(name) {};
		void Display() const;
		void AddElement(DTDElement* element);
		void AddAttList(DTDAttList* attList); 
                
                DTDElement const * SearchForElem( string const & name ) const;

	private :
		vector<DTDElement> elements;
		vector<DTDAttList> attList;
		string name;
};
