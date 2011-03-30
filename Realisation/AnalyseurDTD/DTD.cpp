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
void DTDDocument::display() const
{
	cout << "<!DOCTYPE " << name << " [ " << endl << endl;
	vector <DTDElement>::const_iterator it;
	
	for (it = elements.begin(); it != elements.end(); ++it)
		it->display();
		
	vector <DTDAttList>::const_iterator it_att;
	for (it_att = attList.begin(); it_att != attList.end(); ++it_att)
		it_att->display();
		
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
    vector<DTDElement>::const_iterator elemIt = elements.begin();

    bool found = false;

    while( !found && ( elemIt != elements.end() ) )
    {
        if( ( elemIt->GetName() ).compare( name ) == 0 )
        {
            return &( *elemIt );
        }

        elemIt++;
    }

    return NULL;
}

extern bool dtdparse(const char *, DTDDocument**); 
DTDDocument * DTDDocument::parse (const string & filename)
{
	DTDDocument * dtd;
	if (dtdparse(filename.c_str(), &dtd))
		return dtd;
	return NULL;
}

/************************** DTDElement ******************************/
void DTDElement::display() const
{
	cout << "<!ELEMENT " << name << " ";
	vector <DTDContentspec*>::const_iterator it;
	for (it = contentspec.begin(); it != contentspec.end(); ++it)
		(*it)->display();
	cout << ">" << endl;
}

void DTDElement::Add(DTDContentspec * content)
{
	contentspec.push_back(content);
}

bool DTDElement::ValidateElement( vector<XmlNode *> const * xmlNodeVector ) const
{
    vector<XmlNode *>::const_iterator * nodeIt = new vector<XmlNode *>::const_iterator;
    
    *nodeIt = xmlNodeVector->begin();

    bool result = ( *( contentspec.begin() ) )->IsValidated( nodeIt, xmlNodeVector );

    delete nodeIt;

    return result;
}

/************************** DTDSequence ******************************/
void DTDSequence::display() const
{
	vector <DTDChildren*>::const_iterator it;
	cout << "(";
	for (it = seq.begin(); it != seq.end(); ++it)
	{
		(*it)->display();
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

bool DTDSequence::IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> const * nodeVector ) const
{
    bool result = true;

    if( *xmlNode == nodeVector->end() )
    {
        return false;
    }
    else
    {
        vector<XmlNode *>::const_iterator xmlNodeBackup = *xmlNode;

        vector<DTDChildren *>::const_iterator childrenIt;

        for( childrenIt = seq.begin() ; childrenIt != seq.end() ; childrenIt++ )
        {
            result &= ( *childrenIt )->IsValidated( xmlNode, nodeVector );
        }
    }

    switch( mark )
    {
        case NO_MARK:
        {
            if( !result )
            {
                *xmlNode = xmlNodeBackup;
            }

            return result;
        }

        case M_Q:
        {
            if( !result )
            {
                *xmlNode = xmlNodeBackup;
            }

            return true;
        }

        case M_AST:
        {
            // let's try to validate this sequence another time !
            // No need to backup *xmlNode because it is done in the
            // next level of recurrence (it's complicated)
            bool nestedResult = IsValidated( xmlNode , nodeVector);

            return true;
        }

        case M_PLUS:
        {
            if( result )
            {
                // let's try to validate this sequence another time !
                // No need to backup *xmlNode because it is done in the
                // next level of recurrence (it's complicated)
                bool nestedResult = IsValidated( xmlNode, nodeVector );

                return true;
            }
            else
            {
                *xmlNode = xmlNodeBackup;

                return false;
            }
        }
    }

    return result; // et bim
}

/************************** DTDChoice ******************************/
void DTDChoice::display() const
{
	vector <DTDChildren*>::const_iterator it;
	cout << "(";
	for (it = choice.begin(); it != choice.end(); ++it)
	{
		(*it)->display();
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

bool DTDChoice::IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> const * nodeVector ) const
{
    bool result = false;

    if( *xmlNode == nodeVector->end() )
    {
        result = false;
    }
    else
    {
        vector<XmlNode *>::const_iterator xmlNodeBackup = *xmlNode;

        vector<DTDChildren *>::const_iterator choiceIt = choice.begin();

        while( !result && choiceIt != choice.end() )
        {
            result = ( *choiceIt )->IsValidated( xmlNode, nodeVector );

            choiceIt++;
        }
    }

    switch( mark )
    {
        case NO_MARK:
        {
            if( !result )
            {
                *xmlNode = xmlNodeBackup;
            }

            return result;
        }

        case M_Q:
        {
            if( !result )
            {
                *xmlNode = xmlNodeBackup;
            }

            return true;
        }

        case M_AST:
        {
            // let's try to validate this sequence another time !
            // No need to backup *xmlNode because it is done in the
            // next level of recurrence (it's complicated)
            bool nestedResult = IsValidated( xmlNode, nodeVector );

            return true;
        }

        case M_PLUS:
        {
            if( result )
            {
                // let's try to validate this sequence another time !
                // No need to backup *xmlNode because it is done in the
                // next level of recurrence (it's complicated)
                bool nestedResult = IsValidated( xmlNode, nodeVector );

                return true;
            }
            else
            {
                *xmlNode = xmlNodeBackup;

                return false;
            }
        }
    }

    return result; // et bim
}

/************************** DTDName ******************************/
void DTDName::display() const
{
	cout << name;
	PRINT_MARK
}

bool DTDName::IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> const * nodeVector ) const
{
    bool result;

    if( *xmlNode == nodeVector->end() )
    {
        result = false;
    }
    else
    {
        if( ( *( *xmlNode ) )->isElement() )
        {
            XmlElement * elem = ( XmlElement * )( *( *xmlNode ) );

            result = ( name.compare( elem->nodeName() ) == 0 ); 
        }
        else
        {
            result = ( name.compare( "#PCDATA" ) == 0 );
        }
    }


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
                ( *xmlNode )++;
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
                ( *xmlNode )++;
            }
            return true;
        }

        case M_AST:
        {
            // 0 to n matching elements : consumming them all.
            // No problem if no element found : returning always true.

            if( result )
            {
                ( *xmlNode )++;

                IsValidated( xmlNode, nodeVector );
            }

            return true;
        }

        case M_PLUS:
        {
            // We must have at least one matching element
            if( result )
            {
                ( *xmlNode )++;

                IsValidated( xmlNode, nodeVector );

                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return result;
}

/************************** DTDEmpty ******************************/
bool DTDEmpty::IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> const * nodeVector ) const
{
    return nodeVector->empty();
}

/************************** DTDAny ******************************/
bool DTDAny::IsValidated( vector<XmlNode*>::const_iterator * xmlNode, vector<XmlNode*> const * nodeVector ) const
{
    ( *xmlNode )++;

    return true;
}

/************************** DTDAttList ******************************/
void DTDAttList::Add(DTDAttribute * att)
{
	attList.push_back(*att);
}

void DTDAttList::display() const
{
	cout << "<!ATTLIST " << name << endl;
	vector <DTDAttribute>::const_iterator it;
	for (it = attList.begin(); it != attList.end(); ++it)
		it->display();
	cout << ">" << endl;
}

/************************** DTDAttribute ******************************/
void DTDAttribute::display() const
{
	cout << "\t" << name << " " << type << " " << att << endl;
}
