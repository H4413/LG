%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "DTD.h"
#define YYDEBUG 1

void yyerror(const char *msg);
int yywrap(void);
int yylex(void);

DTDDocument * document;
extern FILE * yyin;
bool dtdErr;
%}

%union 
{
	DTDDocument * dtdd;
	DTDElement * elem;
	DTDContentspec * spec;
	DTDChildren * child;
	std::vector<DTDChildren*>* list_child;
	DTDAttList * attList;
	DTDAttribute * att;
	DTDName * name;
	char *s; 
	Mark mrk;
}

%error-verbose

%type <dtdd> dtd
%type <elem> element
%type <list_child> liste_seq liste_choice
%type <child> children mixed choice choice_plus sequence
%type <spec> contentspec
%type <mrk> plus
%type <att> attribut
%type <attList> att_definition

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%%

main: dtd               
    ;

dtd: dtd ATTLIST NAME att_definition CLOSE 	{$4->SetName($3); 
											 document->AddAttList($4);}
   | dtd ATTLIST NAME att_definition error 	{$4->SetName($3); 
											 document->AddAttList($4);
											 printf("ERROR: Missing : \">\" \n");  
   											dtdErr = true}
   | dtd element 							{document->AddElement($2);}
   | /* empty */                     		{$$ = document;}
   ;
   									
element: ELEMENT NAME contentspec CLOSE 	{$$ = new DTDElement($2);
											 $$->Add($3);}
	| ELEMENT NAME contentspec error	 	{$$ = new DTDElement($2);
											 $$->Add($3);
											 printf("ERROR: Missing : \">\" \n");  
   											dtdErr = true}
	;

contentspec: EMPTY 							{$$ = new DTDEmpty();}
   | ANY 									{$$ = new DTDAny();}
   | mixed 									{$$ = $1;}
   | children 								{$$ = $1;}
   ;

children: sequence plus 					{$$ = $1;}
   | choice plus  							{$$ = $1;}
   ;

choice_plus : sequence plus 				{$$ = $1; $$->AddMark($2);}
   | choice plus 							{$$ = $1; $$->AddMark($2);}
   | NAME plus 								{$$ = new DTDName($1); 
											 $$->AddMark($2);}
   ;

plus : AST 									{$$ = M_AST;}
   | PLUS 									{$$ = M_PLUS;}
   | QMARK 									{$$ = M_Q;}
   | /*empty*/ 								{$$ = NO_MARK;}
   ;

sequence : OPENPAR liste_seq CLOSEPAR 		{$$ = new DTDSequence(); 
											 $$->AddList($2);}
   ;

choice : OPENPAR liste_choice CLOSEPAR 		{$$ = new DTDChoice(); 
											 $$->AddList($2);}
   ;

liste_seq : liste_seq COMMA choice_plus 	{$$ = $1;
											 $$->push_back($3);}
	| choice_plus 							{$$ = new vector<DTDChildren*>;
											 $$->push_back($1);}
	;
	
liste_choice : liste_choice PIPE choice_plus {$$ = $1;
											 $$->push_back($3);}
	| choice_plus 							 {$$ = new vector<DTDChildren*>;
											 $$->push_back($1);}
	;
	
mixed : OPENPAR PCDATA PIPE 
	choice_plus CLOSEPAR AST 			{$$ = new DTDChoice(); 
										 $$->Add(new DTDName("#PCDATA")); 
										 $$->Add($4);}
   | OPENPAR PCDATA CLOSEPAR 			{$$ = new DTDChoice(); 
										 $$->Add(new DTDName("#PCDATA"));}
   ;

att_definition
: att_definition attribut				{$$ = $1; $$->Add($2);}
| /* empty */							{$$ = new DTDAttList();}
;

attribut
: NAME att_type defaut_declaration		{$$ = new DTDAttribute($1);}
;

att_type
: CDATA    
| TOKENTYPE
| type_enumere
;

type_enumere
: OPENPAR liste_enum_plus CLOSEPAR
;

liste_enum_plus
: liste_enum PIPE item_enum
;

liste_enum
: item_enum               
| liste_enum PIPE item_enum
;

item_enum
: NAME
;

defaut_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;
%%


bool dtdparse(const char * dtdname, DTDDocument ** dtd)
{
	int err;
	FILE * dtdfile = NULL;
	dtdErr = false;
	document = new DTDDocument();
	
	if (dtdname)
	{
		dtdfile = fopen(dtdname, "r");
		if (dtdfile)
			yyin = dtdfile;
		else
			printf("%s cannot be open. We will try stdin.\n", dtdname);
	}
	err = yyparse();
	
	if (dtdfile)
	{
		yyin = stdin;
		fclose(dtdfile);
	}
	
	if (dtd)
		*dtd = document;
	else
		delete document;
	
	if (err != 0) 
	{
		printf("Parse ended with %d error(s)\n", err);
		return false;
	}
	else if (dtdErr)
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
	DTDDocument * dtd;
	dtdparse(argv[1], &dtd);
	dtd->display();
	return 0;
}

#endif

int yywrap(void)
{
  return 1;
}

void yyerror(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


