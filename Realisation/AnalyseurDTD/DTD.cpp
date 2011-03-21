/* Implémentation de la DTD */ 

#include "DTD.h"

#include <iostream>

#define PRINT_MARK 			\
	switch (mark)			\
	{						\
		case NO_MARK:		\
			break;			\
		case M_AST:			\
			cout << "*";	\
			break;			\
		case M_PLUS:		\
			cout << "+";	\
			break;			\
		case M_Q:			\
			cout << "?";	\
			break;			\
	}

/************************** DTDDocument ******************************/
void DTDDocument::Display() const
{
	cout << "<!DOCTYPE " << name << " [ " << endl << endl;
	vector <DTDElement>::const_iterator it;
	for (it = elements.begin(); it != elements.end(); ++it)
		it->Display();
	cout << endl << "]>" << endl;
}

void DTDDocument::AddElement(DTDElement* element) 
{
    elements.push_back(*element);
}

void DTDDocument::AddAttribute(string attribute)
{
	attributes.push_back(*(new DTDAttributes(attribute)));
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

void DTDElement::Add(DTDContentspec * content)
{
	contentspec.push_back(content);
}

/************************** DTDSequence ******************************/
void DTDSequence::Display() const
{
	vector <DTDChildren*>::const_iterator it;
	cout << "(";
	for (it = seq.begin(); it != seq.end(); ++it)
	{
		(*it)->Display();
		if (it + 1 != seq.end())
			cout << ", ";
	}
	cout << ")";
	PRINT_MARK
}

void DTDSequence::Add(DTDChildren * child)
{
	seq.push_back(child);
}

void DTDSequence::Add(string name)
{
	seq.push_back(new DTDName(name));
}

ChildType DTDSequence::getType()
{
    return SEQUENCE;
}

/************************** DTDChoice ******************************/
void DTDChoice::Display() const
{
	vector <DTDChildren*>::const_iterator it;
	cout << "(";
	for (it = choice.begin(); it != choice.end(); ++it)
	{
		(*it)->Display();
		if (it + 1 != choice.end())
			cout << " | ";
	}
	cout << ")";
	PRINT_MARK

}

void DTDChoice::Add(DTDChildren * child)
{
	choice.push_back(child);
}

void DTDChoice::Add(string name)
{
	choice.push_back(new DTDName(name));
}

ChildType DTDChoice::getType()
{
    return CHOICE;
}

/************************** DTDName ******************************/
void DTDName::Display() const
{
	cout << name;
	PRINT_MARK
}

ChildType DTDName::getType()
{
    return NAME;
}

