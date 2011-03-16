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

    DTDAttributs(string name, type = "CDATA", att = "#IMPLIED") : name(name),type(type),att(att){};

    private :

    string name;
    string type;
    string att;

};

class DTDChildren : public DTDContentspec {

	public :

    void Display();
};

class DTDSequence : public DTDChildren {

	public :

	DTDSequence(string seq) : seq(seq) {};
    void Display();

	protected :

	string seq;
};

class DTDChoice : public DTDChildren {
	public :

	DTDChoice(vector<DTDChildren> choice) choice(choice){};
    void Display();

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

	DTDElement(map<string, DTDContentspec> contentspec) : contentspec(contentspec) {};

	private:
	
	map<string, DTDContentspec> contentspec;
	
};

class DTDDocument {
	public :

	DTDDocument(map<string, DTDElement> & elements) : elements(elements){};

	private :

	map<string, DTDElement> elements;
};
