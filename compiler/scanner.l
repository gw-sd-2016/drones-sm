%{
#include "parser.tab.h" 
#include "defines.h"
%}

D [a-zA-Z]+[a-zA-Z0-9]*
I [0-9]+
%option yylineno
%%

program {return PROGRAM ;}
"("	{yylval.string = "("; return ROPAR;}
")"	{yylval.string = ")"; return RCPAR;}
"{"	{return ROBRK;}
"}"	{return RCBRK;}
";"	{return SEMICOLON;}
"."	{return DOT;}
","	{return COMMA;}
"var"	{return VAR;}
":"	{return COLON;}
"string"	{return STRING;}
"integer"	{return INTEGER;}
"real"	{return REAL;}
"#States"	{return BEGINT;}
"#EndStates"	{return END;}
"State"	{return STATE_DEC;}
"transition" {eprintf("FOUND TRANSITION\n"); return TRANSITION;}
"print"	{eprintf("print statement\n"); return PRINTF;}
\".*\"	{yylval.string = (char*)strdup(yytext); return QUOTE;}
\#"include"\".*\"	{eprintf("OTHER SHIT FOUND\n"); yylval.string = (char*)strdup(yytext); return INCLUDE;}
\#"include"\<.*\>	{yylval.string = (char*)strdup(yytext); return INCLUDE;}
"insert_c{".*\}	{printf("SHIT FOUND %s\n", yytext); yylval.string = (char*)strdup(yytext); return INSERT_C;}
"="	{return ASSIGNOP;}
"if"	{return IF;}
"for"	{return FOR;}
"then"	{return THEN;}
"else"	{return ELSE;}
"do"	{return DO;}
"<"     {yylval.string = "<"; return RELOP;}
">"     {yylval.string = ">"; return RELOP;}
"<="	  {yylval.string = "<="; return RELOP;}
">="	  {yylval.string = ">="; return RELOP;}
"=="     {yylval.string = "=="; return RELOP;}
"!="	  {yylval.string = "!="; return RELOP;}
"+" 	  {yylval.string = "+"; return ADDOP;}
"-"     {yylval.string = "-"; return ADDOP;}
"*" 	  {yylval.string = "*"; return ADDOP;}
"/"     {yylval.string = "/"; return ADDOP;}
"!"	{yylval.string = "!"; return ADDOP;}
">>"	{yylval.string = ">>"; return ADDOP;}
"<<"	{yylval.string = "<<"; return ADDOP;}
"&"	{yylval.string = "&"; return ADDOP;}
"^"	{yylval.string = "^"; return ADDOP;}
"%"	{yylval.string = "%"; return ADDOP;}
"|"	{yylval.string = "|"; return ADDOP;}
"&&"	{return AND;}
"||"	{return OR;}

{I}	{yylval.integer = atoi(yytext);return INT;}
{I}\.{I}	{yylval.real = atof(yytext);return REALNO;}

{D}\((({I}|{D}|({I}\.{I}))[ ]*\,)*[ ]*({I}|{D}|({I}\.{I}))?\)	{eprintf("FUNCTION: %s\n", yytext);yylval.string = (char*)strdup(yytext);return FUNC;}
{D}	{yylval.string = (char*)strdup(yytext);return ID;}

[ ]*{D}[ ]*\=[ ]*({I}|{D})[ ]*\;[ ]*{D}[ ]*(\<|\>)?\=[ ]*({I}|{D})[ ]*\;[ ]*(((\+\+|\-\-){D})|({D}(\+\+|\-\-)))[ ]* {eprintf("FOR[%s]\n", yytext);
       yylval.string = (char*)strdup(yytext); return FOR_EXPRESSION;}

[ \t\r\n]+	;	
.	          {printf("unrecognized text: %s\n",yytext);}

%%
//TODO Reevaluate FUNC, it can end in a comma
