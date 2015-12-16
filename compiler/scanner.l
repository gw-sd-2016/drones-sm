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
\#"include"\".*\"|\#"include"\ \".*\"	{eprintf("OTHER FOUND\n"); yylval.string = (char*)strdup(yytext); return INCLUDE;}
\#"include"\<.*\>|\#"include"\ \<.*\>	{yylval.string = (char*)strdup(yytext); return INCLUDE;}
"insert_c{".*\}	{printf("STUFF FOUND %s\n", yytext); yylval.string = (char*)strdup(yytext); return INSERT_C;}
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
"++"|"--"	{yylval.string = (char*)strdup(yytext);return PPMM;}
{I}	{yylval.integer = atoi(yytext);return INT;}
{I}\.{I}	{yylval.real = atof(yytext);return REALNO;}

{D}\((({I}|{D}|({I}\.{I}))[ ]*\,)*[ ]*({I}|{D}|({I}\.{I}))?\)	{eprintf("FUNCTION: %s\n", yytext);yylval.string = (char*)strdup(yytext);return FUNC;}
{D}	{yylval.string = (char*)strdup(yytext);return ID;}

[ \t\r\n]+	;	
.	          {printf("unrecognized text: %s\n",yytext);}
%%
//TODO Reevaluate FUNC, it can end in a comma
