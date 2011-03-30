%{

using namespace std;
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Xml.h"
#include "commun.h"
#include "xx.tab.h"

int xxwrap(void);
void xxerror(const char *msg);
int xxlex(void);

XmlDoc * xmlDoc;
extern FILE * xxin;
bool xmlErr;

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
   XmlDoc * doc;
   XmlNode * balise;
   AttributeList* att;
   vector<XmlNode*>* list_cont;

}

%error-verbose

%type <doc> document
%type <balise> element 
%type <att> attribut
%type <list_cont> empty_or_content close_content_and_end content
%type <en> start
%type <s> name_or_nsname_opt

%token EQ SLASH CLOSE END CLOSESPECIAL DOCTYPE
%token <s> ENCODING VALUE DATA COMMENT NAME NSNAME
%token <en> NSSTART START STARTSPECIAL

%%

document
 : declarations element misc_seq_opt 	{xmlDoc->SetRoot($2);}
 ;

misc_seq_opt
 : misc_seq_opt misc
 | /* empty */
 ;
misc
 : COMMENT		
 ;

declarations
 : declarations declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE NAME NAME VALUE CLOSE		{xmlDoc->SetDTD (new DTD($2, $4));}
 | STARTSPECIAL attribut CLOSESPECIAL
 ;

element
 : start attribut					
   empty_or_content 				{$$ = new XmlElement($1->second);
									 ((XmlElement*)$$)->SetAttributsList($2);
									 ((XmlElement*)$$)->SetChildren($3);
									 }
 ;
start
 : START							{$$ = $1;}
 | NSSTART							{$$ = $1;}
 ;

empty_or_content
 : SLASH CLOSE						{$$ = new vector<XmlNode*>;}
 | close_content_and_end 			
   name_or_nsname_opt CLOSE 		{$$ = $1;}
 | close_content_and_end 			
   name_or_nsname_opt error			{printf("ERROR: Missing "
   										"\">\" in the markup %s! \n", $2); 
   									xmlErr = true;
   									$$ = $1;}
 | close_content_and_end 			
   error							{printf("ERROR: You forget to close "
   										"the markup! \n"); 
   									xmlErr = true;
   									$$ = $1;}
 ;
name_or_nsname_opt 
 : NAME     						{$$ = $1;}
 | NSNAME  							{$$ = $1;}
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END 								{$$ = $2;}
 | error content END				{printf("ERROR: Missing : \">\" \n");  
   									xmlErr = true;
   									$$ = $2;}
 | CLOSE content error				{printf("ERROR: Missing : \"<\" \n"); 
   									xmlErr = true;
   									$$ = $2;}
 ;
content 
 : content DATA						{$$ = $1; $$->push_back(new XmlContent($2));}
 | content misc						{$$ = $1;}
 | content element      			{$$ = $1; $$->push_back($2);}
 | /*empty*/         				{$$ = new vector<XmlNode*>;}
 ;

attribut
 : attribut NAME EQ VALUE			{$$ = $1;
									 $$->insert(Attribute($2, new XmlAtt($2, $4)));}
 | attribut NAME EQ error			{$$ = $1;
									 $$->insert(Attribute($2, new XmlAtt($2, "")));
									printf("ERROR: Missing attribute value"
										" for %s.\n", $2); 
   									xmlErr = true;}
 | attribut error EQ VALUE			{$$ = $1;
									printf("ERROR: Attribute with value,"
										" but no name.\n"); 
   									xmlErr = true;}
 | /* empty */						{$$ = new AttributeList;}
 ;
%%

bool xmlparse(const char * xmlname, XmlDoc ** xml)
{
	int err;
	FILE * xmlfile = NULL;
	xmlErr = false;
	xmlDoc = new XmlDoc();
	
	if (xmlname)
	{
		xmlfile = fopen(xmlname, "r");
		if (xmlfile)
			xxin = xmlfile;
		else
			printf("%s cannot be open. We will try stdin.\n", xmlname);
	}
	
	err = xxparse();
	
	if (xmlfile)
	{
		xxin = stdin;
		fclose(xmlfile);
	}
	
	if (xml)
		*xml = xmlDoc;
	else
		delete xmlDoc;
		
	if (err != 0) 
	{
		printf("Parse ended with %d error(s).\n", err);
		return false;
	}
	else if (xmlErr)
	{
		printf("Parse ended with not critical error(s).\n");
		printf("All error(s) was recovered.\n");
		return false;
	}
	else	
	{  
		printf("Parse ended with sucess\n");
		return true;
	}

}

#ifndef NDEBUG

int main(int argc, char **argv)
{
	XmlDoc * xml;
	xmlparse(argv[1], xml);
	xml->Display();
	return 0;
}

#endif

int xxwrap(void)
{
  return 1;
}

void xxerror(const char *msg)
{
	fprintf(stderr, "Problem: %s\n", msg);
}
