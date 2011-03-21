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

class DTDContentspec {

	public :

	virtual void Display() const = 0;

};

class DTDAttribute {
    
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
		
	public:
		DTDAttList () {}
		void Add (DTDAttribute * att);
		
};

class DTDChildren : public DTDContentspec 
{
	protected:
	Mark mark;
	
	public :
	DTDChildren() : mark(NO_MARK) {}
	virtual void Add(DTDChildren * child) {}
	virtual void AddMark(Mark a_mark) {mark = a_mark;}
    virtual void Display() const = 0;
    bool HasAMark() const {return mark != NO_MARK;}
};

class DTDSequence : public DTDChildren {

	public :
    DTDSequence() {}
    void Display() const;
    void Add(DTDChildren* child);
    void Add(string name);

	protected :

	vector<DTDChildren*> seq;
};

class DTDChoice : public DTDChildren {
	public :

    DTDChoice() {}
    void Display() const;
    void Add(DTDChildren* child);
    void Add(string name);

	vector<DTDChildren*> choice;
	private :
	
	
};

class DTDName : public DTDChildren {
	public :

	DTDName(string name) : name(name){};
    void Display() const;

	private :

	string name;
};

class DTDEmpty : public DTDContentspec {

	public :
	
	DTDEmpty();
	void Display() const;

};

class DTDAny : public DTDContentspec {
	
	public :

	DTDAny(string content): content(content){};
	void Display() const;

	private : 

	string content;
};

class DTDElement {

	public :
    
    DTDElement() {}
    DTDElement(string name) : name(name) {};
    void Display() const;
    void Add(DTDContentspec * content);

	private:
	string name;
	vector<DTDContentspec*> contentspec;
	
};

class DTDDocument {
	public :
    
    DTDDocument() {}
    DTDDocument(string name) : name(name) {};
    void Display() const;
    void AddElement(DTDElement* element);
    void AddAttribute(string attribute); 

	private :

	vector<DTDElement> elements;
    DTDAttList attributes;
    string name;
};
