%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "DTD.h"
#define YYDEBUG 1

void yyerror(char *msg);
int yywrap(void);
int yylex(void);

DTDDocument * document = new DTDDocument();
%}

%union {
	DTDDocument * dtdd;
	DTDElement * elem;
	DTDContentspec * spec;
	DTDChildren * child;
	DTDName * name;
	char *s; 
	Mark mrk;
}

%type <dtdd> dtd
%type <elem> element
%type <child> children mixed choice choice_plus liste_choice sequence liste_seq
%type <spec> contentspec
%type <mrk> plus

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%%

main: dtd               
    ;

dtd: dtd ATTLIST NAME att_definition CLOSE {document->AddAttribute($3);}
   | dtd element {document->AddElement($2);}
   | /* empty */                     
   ;

element: ELEMENT NAME contentspec CLOSE {$$ = new DTDElement($2);
										  $$->Add($3);}
	;

contentspec: EMPTY {$$ = new DTDChoice();}
   | ANY {$$ = new DTDChoice();}
   | mixed {$$ = $1;}
   | children {$$ = $1;}
   ;

children: sequence plus {$$ = $1;}
   | choice plus  {$$ = $1;}
   ;

choice_plus : sequence plus {$$ = $1; $$->AddMark($2);}
   | choice plus {$$ = $1; $$->AddMark($2);}
   | NAME plus {$$ = new DTDName($1); $$->AddMark($2);}
   ;

plus : AST {$$ = M_AST;}
   | PLUS {$$ = M_PLUS;}
   | QMARK {$$ = M_Q;}
   | /*empty*/ {$$ = NO_MARK;}
   ;

sequence : OPENPAR liste_seq CLOSEPAR {$$ = new DTDSequence(); $$->Add($2);}
   ;

choice : OPENPAR liste_choice CLOSEPAR {$$ = new DTDChoice(); $$-> Add($2);}
   ;

liste_seq : liste_seq COMMA choice_plus {$$ = new DTDSequence();
										$$->Add($1); $$->Add($3);}
   |choice_plus {$$ = $1;}
	;
	
liste_choice : liste_choice PIPE choice_plus {$$ = new DTDChoice();
										$$->Add($1); $$->Add($3);}
   |choice_plus {$$ = $1;}
	;
	
mixed : OPENPAR PCDATA PIPE choice_plus CLOSEPAR AST { $$ = new DTDChoice(); $$->Add(new DTDName("#PCDATA")); $$->Add($4); }
   | OPENPAR PCDATA CLOSEPAR {$$ = new DTDChoice(); $$->Add(new DTDName("#PCDATA"));}
   ;

att_definition
: att_definition attribut
| /* empty */
;

attribut
: NAME att_type defaut_declaration
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
int main(int argc, char **argv)
{
  int err;
  yydebug = 1;

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with sucess\n", err);
        
  document->Display();
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


