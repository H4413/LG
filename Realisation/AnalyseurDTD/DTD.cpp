/* Implémentation de la DTD */ 

#include "DTD.h"

#include <iostream>

/************************** DTDDocument ******************************/
void DTDDocument::Display() const
{
	cout << "<!DOCTYPE " << name << " [ " << endl << endl;
	map <string, DTDElement>::const_iterator it;
	for (it = elements.begin(); it != elements.end(); ++it)
		it->second.Display();
	cout << endl << "]>";
}

bool DTDDocument::AddElement(string element) 
{
    DTDElement el(element);
    elements.add(el);
    return True;
}

bool DTDDocument::AddAttributes(string attribute)
{
    DTDAttributes
}

/************************** DTDElement ******************************/
void DTDElement::Display() const
{
	cout << "<!ELEMENT " << name << " ";
	vector <DTDContentspec*>::const_iterator it;
	for (it = contentspec.begin(); it != contentspec.end(); ++it)
		(*it)->Display();
	cout << ">" << endl;
}

/************************** DTDSequence ******************************/
void DTDSequence::Display() const
{
	vector <DTDChildren*>::const_iterator it;
	cout << "(";
	for (it = seq.begin(); it != seq.end(); ++it)
		(*it)->Display();
	cout << ")";
}

/************************** DTDChoice ******************************/
void DTDChoice::Display() const
{
	vector <DTDChildren*>::const_iterator it;
	cout << "(";
	for (it = choice.begin(); it != choice.end(); ++it)
		(*it)->Display();
	cout << ")";
}

/************************** DTDNom ******************************/
void DTDNom::Display() const
{
	cout << name;
}
