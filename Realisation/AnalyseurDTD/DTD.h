/* Interface de la DTD */

#include <vector>
#include <map>
#include <string>
using namespace std;

class DTDContentspec {

	public :

	virtual void Display() = 0;

};

class DTDAttributes {
    
    public:

    DTDAttributes(string name, type = "CDATA", att = "#IMPLIED") : name(name),type(type),att(att){};
    void Display();
    
    private :

    string name;
    string type;
    string att;

};

class DTDChildren : public DTDContentspec {

	public :

    virtual void Display() = 0;
};

class DTDSequence : public DTDChildren {

	public :
    DTDSequence();
    void Display();
    bool Add(DTDChildren child);

	protected :

	vector<DTDChildren> seq;
};

class DTDChoice : public DTDChildren {
	public :

    DTDChoice();
    void Display();
    bool Add(DTDChildren child);

	private :
	
	vector<DTDChildren> choice;
};

class DTDNom : public DTDChildren {
	public :

	DTDNom(string name) : name(name){};
    void Display();

	private :

	string name;
};

class DTDEmpty : public DTDContentspec {

	public :
	
	DTDEmpty();
	void Display();

};

class DTDAny : public DTDContentspec {
	
	public :

	DTDAny(string content): content(content){};
	void Display();

	private : 

	string content;
};

class DTDElement {

	public :
    
    DTDElement();
    DTDElement(string name) : name(name) {};
    void Display();
    bool Add(DTDContentspec content);

	private:
	string name;
	vector<DTDContentspec> contentspec;
	
};

class DTDDocument {
	public :
    
    DTDDocument();
    DTDDocument(string name) : name(name) {};
    void Display();
    bool Add(DTDElement element);

	private :

	map<string, DTDElement> elements;
    map<string, DTDAttributes> attributes;
    string name;
};
