%option 8bit nodefault

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "yy.tab.h"

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
<INITIAL>{element}            {printf("%s",yytext); BEGIN(INSIDE); return ELEMENT; }
<INITIAL>{attlist}            {printf("%s",yytext); BEGIN(INSIDE); return ATTLIST; }
<INSIDE>{close}               {printf("%s",yytext); BEGIN(INITIAL); return CLOSE; }
<INSIDE>{openpar}             {printf("%s",yytext); return OPENPAR; }
<INSIDE>{closepar}{ws}?       {printf("%s",yytext); return CLOSEPAR; }
<INSIDE>{comma}{ws}?          {printf("%s",yytext); return COMMA; }
<INSIDE>{pipe}{ws}?           {printf("%s",yytext); return PIPE; }
<INSIDE>{declaration}         {printf("%s",yytext); stringreturn(DECLARATION); }
<INSIDE>{fixed}               {printf("%s",yytext); return FIXED; }
<INSIDE>{ast}                 {printf("%s",yytext); return AST ; }
<INSIDE>{qmark}               {printf("%s",yytext); return QMARK ; }
<INSIDE>{plus}                {printf("%s",yytext); return PLUS ; }
<INSIDE>{empty}               {printf("%s",yytext); return EMPTY; }
<INSIDE>{any}                 {printf("%s",yytext); return ANY; }
<INSIDE>{pcdata}              {printf("%s",yytext); return PCDATA; }
<INSIDE>{cdata}               {printf("%s",yytext); return CDATA; }
<INSIDE>{string}              {printf("%s",yytext); stringreturn(STRING); }
<INSIDE>{tokentype}{ws}?      {printf("%s",yytext); stringreturn(TOKENTYPE); }
<INSIDE>{name}{ws}?           {printf("%s",yytext); stringreturn(NAME); }
{comment}		               {printf("%s",yytext); /* skip comments stringreturn(COMMENT); */ }

.			{printf("%s",yytext);fprintf(stderr, "!ERROR(%c)\n", *yytext);}
{nl}			{printf("%s",yytext);/* skip, must be an extra one at EOF */;}
