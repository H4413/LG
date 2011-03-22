/* Implémentation de la DTD */ 

#include "DTD.h"
#include "Xml.h"

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

DTDElement const * DTDDocument::SearchForElem( string const & name ) const
{
    // TODO

    return NULL;
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

void DTDSequence::AddList(vector<DTDChildren*>* list)
{
    vector <DTDChildren*>::const_iterator it;
    for (it = list->begin(); it != list->end(); ++it)
    {
        seq.push_back(*it);
    }
}

bool DTDSequence::IsValidated( vector<XmlElement*>::const_iterator * xmlElem ) const
{
    vector<XmlElement *>::const_iterator xmlElemBackup = *xmlElem;

    vector<DTDChildren *>::const_iterator childrenIt;

    bool result = true;

    for( childrenIt = seq.begin() ; childrenIt != seq.end() ; childrenIt++ )
    {
        result &= ( *childrenIt )->IsValidated( xmlElem );
    }

    switch( mark )
    {
        case NO_MARK:
        {
            if( !result )
            {
                *xmlElem = xmlElemBackup;
            }

            return result;
        }

        case M_Q:
        {
            if( !result )
            {
                *xmlElem = xmlElemBackup;
            }

            return true;
        }

        case M_AST:
        {
            // let's try to validate this sequence another time !
            // No need to backup *xmlElem because it is done in the
            // next level of recurrence (it's complicated)
            bool nestedResult = IsValidated( xmlElem );

            return true;
        }

        case M_PLUS:
        {
            if( result )
            {
                // let's try to validate this sequence another time !
                // No need to backup *xmlElem because it is done in the
                // next level of recurrence (it's complicated)
                bool nestedResult = IsValidated( xmlElem );

                return true;
            }
            else
            {
                *xmlElem = xmlElemBackup;

                return false;
            }
        }
    }

    return result; // et bim
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

void DTDChoice::AddList(vector<DTDChildren*>* list)
{
	vector <DTDChildren*>::const_iterator it;
	for (it = list->begin(); it != list->end(); ++it)
	{
		choice.push_back(*it);
	}
}

bool DTDChoice::IsValidated( vector<XmlElement*>::const_iterator * xmlElem) const
{
    vector<XmlElement *>::const_iterator xmlElemBackup = *xmlElem;

    vector<DTDChildren *>::const_iterator choiceIt = choice.begin();

    bool result = false;

    while( !result && choiceIt != choice.end() )
    {
        result = ( *choiceIt )->IsValidated( xmlElem );
    }

    switch( mark )
    {
        case NO_MARK:
        {
            if( !result )
            {
                *xmlElem = xmlElemBackup;
            }

            return result;
        }

        case M_Q:
        {
            if( !result )
            {
                *xmlElem = xmlElemBackup;
            }

            return true;
        }

        case M_AST:
        {
            // let's try to validate this sequence another time !
            // No need to backup *xmlElem because it is done in the
            // next level of recurrence (it's complicated)
            bool nestedResult = IsValidated( xmlElem );

            return true;
        }

        case M_PLUS:
        {
            if( result )
            {
                // let's try to validate this sequence another time !
                // No need to backup *xmlElem because it is done in the
                // next level of recurrence (it's complicated)
                bool nestedResult = IsValidated( xmlElem );

                return true;
            }
            else
            {
                *xmlElem = xmlElemBackup;

                return false;
            }
        }
    }

    return result; // et bim
}

/************************** DTDName ******************************/
void DTDName::Display() const
{
	cout << name;
	PRINT_MARK
}

bool DTDName::IsValidated( vector<XmlElement*>::const_iterator * xmlElem ) const
{
    bool result;

    result = ( name.compare( ( *( *xmlElem ) )->GetName() ) == 0 ); 

    // The idea is to advance the iterator throught the elements' vector
    // according to the mark. Whatever happens, the iterator is left just
    // after the last validated xml element (so it can eventually not
    // move).
    switch( mark )
    {
        case NO_MARK:
        {
            // We must find one and only one matching element. Possible
            // other matching elements are left to further analysis.
            if( result )
            {
                ( *xmlElem )++;
            }
            return result;
        }

        case M_Q:
        {
            // We must find one or zero matching element. Possible
            // other matching elements are left to further analysis.
            // It's no problem if we don't find any matching elem, so we
            // always return true.
            if( result )
            {
                ( *xmlElem )++;
            }
            return true;
        }

        case M_AST:
        {
            // 0 to n matching elements : consumming them all.
            // No problem if no element found : returning always true.
            while( result )
            {
                ( *xmlElem )++;

                while( *( *xmlElem ) != NULL )
                {
                    result = ( name.compare( ( *( *xmlElem ) )->GetName() ) == 0 ); 
                }
            }

            return true;
        }

        case M_PLUS:
        {
            // We must have at least one matching element
            if( !result )
            {
                return false;
            }

            while( result )
            {
                ( *xmlElem )++;

                while( *( *xmlElem ) != NULL )
                {
                    result = ( name.compare( ( *( *xmlElem ) )->GetName() ) == 0 ); 
                }
            }

            return true;
        }
    }

    return result;
}

/************************** DTDEmpty ******************************/
bool DTDEmpty::IsValidated( vector<XmlElement*>::const_iterator * xmlElem ) const
{
    return ( ( *( *xmlElem ) )->IsEmpty() );
}

/************************** DTDAny ******************************/
bool DTDAny::IsValidated( vector<XmlElement*>::const_iterator * xmlElem ) const
{
    return true;
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
