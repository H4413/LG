%{

using namespace std;
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Xml.h"
#include "commun.h"
#include "yy.tab.h"

int yywrap(void);
void yyerror(char *msg);
int yylex(void);

XmlDoc * xmlDoc = new XmlDoc();

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
   XmlDoc * doc;
   XmlNode * balise;
   vector<XmlAtt*>* att;

}

%type <doc> document
%type <balise> element content
%type <att> attribut

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
 : DOCTYPE NAME NAME VALUE CLOSE		{xmlDoc->setDTD (new DTD($2));}
 | STARTSPECIAL attribut CLOSESPECIAL
 ;

element
 : start attribut					{//$$ = new XmlElement(NULL);
									 //$$->SetAttList($2);
									}
   empty_or_content 		
 ;
start
 : START		
 | NSSTART	
 ;

empty_or_content
 : SLASH CLOSE	
 | close_content_and_end 
   name_or_nsname_opt CLOSE 
 ;
name_or_nsname_opt 
 : NAME     
 | NSNAME  
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END 
 ;
content 
 : content DATA		
 | content misc        
 | content element      
 | /*empty*/         
 ;

attribut
 : attribut NAME EQ VALUE			{$$ = $1;
									 $$->push_back(new XmlAtt($2, $4));}
 | /* empty */						{$$ = new vector<XmlAtt*>;}
 ;
%%

int main(int argc, char **argv)
{
  int err;

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
  	else  printf("Parse ended with sucess\n", err);
  
  xmlDoc->Display();
  return 0;
}

int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

