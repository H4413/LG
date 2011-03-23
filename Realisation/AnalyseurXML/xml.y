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

#ifndef NDEBUG
#	include "parser.h"
#endif

int xxwrap(void);
void xxerror(char *msg);
int xxlex(void);

XmlDoc * xmlDoc;
extern FILE * xxin;

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
   XmlDoc * doc;
   XmlNode * balise;
   vector<XmlAtt*>* att;
   vector<XmlNode*>* list_cont;

}

%type <doc> document
%type <balise> element 
%type <att> attribut
%type <list_cont> empty_or_content close_content_and_end content
%type <en> start

%token EQ SLASH CLOSE END CLOSESPECIAL DOCTYPE
%token <s> ENCODING VALUE DATA COMMENT NAME NSNAME
%token <en> NSSTART START STARTSPECIAL

%%

document
 : declarations element misc_seq_opt 	{xmlDoc->setRoot($2);}
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
 : DOCTYPE NAME NAME VALUE CLOSE		{xmlDoc->setDTD (new DTD($2, $4));}
 | STARTSPECIAL attribut CLOSESPECIAL
 ;

element
 : start attribut					
   empty_or_content 				{$$ = new XmlElement(NULL, $1->second);
									 ((XmlElement*)$$)->SetAttList($2);
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
 ;
name_or_nsname_opt 
 : NAME     
 | NSNAME  
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END 								{$$ = $2;}
 ;
content 
 : content DATA						{$$ = $1; $$->push_back(new XmlContent(NULL, $2));}
 | content misc						{$$ = $1;}
 | content element      			{$$ = $1; $$->push_back($2);}
 | /*empty*/         				{$$ = new vector<XmlNode*>;}
 ;

attribut
 : attribut NAME EQ VALUE			{$$ = $1;
									 $$->push_back(new XmlAtt($2, $4));}
 | /* empty */						{$$ = new vector<XmlAtt*>;}
 ;
%%

bool xmlparse(const char * xmlname, XmlDoc * xml)
{
	int err;
	xmlDoc = new XmlDoc();
	if (xmlname)
	{
		FILE * xmlfile = fopen(xmlname, "r");
		if (xmlfile)
			xxin = xmlfile;
		else
			printf("%s cannot be open. We will try stdin.", xmlname);
	}
	err = xxparse();
	if (xml)
		xml = xmlDoc;
	else
		delete xmlDoc;
	if (err != 0) 
	{
		printf("Parse ended with %d error(s)\n", err);
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

void xxerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

