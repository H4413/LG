%option 8bit nodefault

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "DTD.h"
#include "yy.tab.h"

extern bool verbose_flag;

#define PRINT_YYTEXT			\
({								\
	if (verbose_flag)			\
		printf("%s", yytext);	\
})

static char* skipSpace(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return strdup(buf);
}
  
/* affecte la valeur de la chaine de caractère et renvoie le token */
#define stringreturn(tokenval) yylval.s=skipSpace(yytext);return(tokenval)

%}
%option noyywrap

nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{nl}?"<"
close		">"{nl}?
openpar "("
closepar ")"
comma ","
pipe "|"
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
tokentype "ID"|"IDREF"|"IDREFS"|"ENTITY"|"ENTITIES"|"NMTOKEN"|"NMTOKENS"
name		{namestart}{namechar}*
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
element {open}"!ELEMENT"{ws}
attlist {open}"!ATTLIST"{ws}
declaration "#"("REQUIRED"|"IMPLIED"){ws}?
fixed "#FIXED"{ws}
pcdata "#PCDATA"{ws}?
cdata "CDATA"{ws}?
qmark "?"
ast "*"
plus "+"
empty "EMPTY"
any "ANY"

%s INSIDE

/* 
   INITIAL : en dehors d'un bloc ELEMENT ou ATTLIST
   INSIDE : dans un bloc ELEMENT ou ATTLIST
*/

%%

<INITIAL>{ws}		            { /* skip */}
<INITIAL>{element}            {PRINT_YYTEXT; BEGIN(INSIDE); return ELEMENT; }
<INITIAL>{attlist}            {PRINT_YYTEXT; BEGIN(INSIDE); return ATTLIST; }
<INSIDE>{close}               {PRINT_YYTEXT; BEGIN(INITIAL); return CLOSE; }
<INSIDE>{openpar}             {PRINT_YYTEXT; return OPENPAR; }
<INSIDE>{closepar}{ws}?       {PRINT_YYTEXT; return CLOSEPAR; }
<INSIDE>{comma}{ws}?          {PRINT_YYTEXT; return COMMA; }
<INSIDE>{pipe}{ws}?           {PRINT_YYTEXT; return PIPE; }
<INSIDE>{declaration}         {PRINT_YYTEXT; stringreturn(DECLARATION); }
<INSIDE>{fixed}               {PRINT_YYTEXT; return FIXED; }
<INSIDE>{ast}                 {PRINT_YYTEXT; return AST ; }
<INSIDE>{qmark}               {PRINT_YYTEXT; return QMARK ; }
<INSIDE>{plus}                {PRINT_YYTEXT; return PLUS ; }
<INSIDE>{empty}               {PRINT_YYTEXT; return EMPTY; }
<INSIDE>{any}                 {PRINT_YYTEXT; return ANY; }
<INSIDE>{pcdata}              {PRINT_YYTEXT; return PCDATA; }
<INSIDE>{cdata}               {PRINT_YYTEXT; return CDATA; }
<INSIDE>{string}              {PRINT_YYTEXT; stringreturn(STRING); }
<INSIDE>{tokentype}{ws}?      {PRINT_YYTEXT; stringreturn(TOKENTYPE); }
<INSIDE>{name}{ws}?           {PRINT_YYTEXT; stringreturn(NAME); }
{comment}		              {PRINT_YYTEXT; /* skip comments stringreturn(COMMENT); */ }

.							 {printf("%s",yytext);fprintf(stderr, "!ERROR(%c)\n", *yytext);}
{nl}						 {printf("%s",yytext);/* skip, must be an extra one at EOF */;}
