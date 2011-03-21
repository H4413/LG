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
		
	vector <DTDAttList>::const_iterator it_att;
	for (it_att = attList.begin(); it_att != attList.end(); ++it_att)
		it_att->Display();
		
	cout << endl << "]>" << endl;
}

void DTDDocument::AddElement(DTDElement* element) 
{
    elements.push_back(*element);
}

void DTDDocument::AddAttList(DTDAttList* atts)
{
	attList.push_back(*atts);
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
	if (child->getType() == DTDSEQUENCE)
    {
	    seq.push_back(child);
    }
    else
    {
        seq.push_back(child);
    }
}

void DTDSequence::Add(string name)
{
	seq.push_back(new DTDName(name));
}

ChildType DTDSequence::getType()
{
    return DTDSEQUENCE;
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
    if (child->getType() == DTDCHOICE)
    {
	    choice.push_back(child);
    }
    else
    {
        choice.push_back(child);
    }
}

void DTDChoice::Add(string name)
{
	choice.push_back(new DTDName(name));
}

ChildType DTDChoice::getType()
{
    return DTDCHOICE;
}

/************************** DTDName ******************************/
void DTDName::Display() const
{
	cout << name;
	PRINT_MARK
}

ChildType DTDName::getType()
{
    return DTDNAME;
}

/************************** DTDAttList ******************************/
void DTDAttList::Add(DTDAttribute * att)
{
	attList.push_back(*att);
}

void DTDAttList::Display() const
{
	cout << "<!ATTLIST " << name << endl;
	vector <DTDAttribute>::const_iterator it;
	for (it = attList.begin(); it != attList.end(); ++it)
		it->Display();
	cout << ">" << endl;
}

/************************** DTDAttribute ******************************/
void DTDAttribute::Display() const
{
	cout << "\t" << name << " " << type << " " << att << endl;
}
