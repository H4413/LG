%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define YYDEBUG 1

void yyerror(char *msg);
int yywrap(void);
int yylex(void);
%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING
%%

main: dtd                           
    ;

dtd: dtd ATTLIST NAME 
     att_definition CLOSE            
   | dtd element 
   | /* empty */                     
   ;

element: ELEMENT NAME contentspec CLOSE;

contentspec: EMPTY
   | ANY
   | mixed
   | children
   ;

children: seq plus
   | choice plus
   ;

choice_plus : seq plus
   | choice plus
   | NAME plus
   ;

plus : AST
   | PLUS
   | QMARK
   | /*empty*/ 
   ;

seq : OPENPAR liste_seq CLOSEPAR
   ;

choice : OPENPAR liste_choice CLOSEPAR
   ;

liste_seq : liste_seq COMMA choice_plus
   |choice_plus;

liste_choice : liste_choice PIPE choice_plus
   |choice_plus;

mixed : OPENPAR PCDATA PIPE choice_plus CLOSEPAR AST
   | OPENPAR PCDATA CLOSEPAR
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


