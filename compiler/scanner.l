%{
#include "parser.tab.h" 
#include "defines.h"
%}

D [a-zA-Z]+[a-zA-Z0-9\_\.\-\>]*
I -?[0-9]+
R -?[0-9]+"."[0-9]+
UR [0-9]*\.[0-9]+
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
"sleep("{UR}")"|"sleep("{I}")"|"usleep("{UR}")"|"usleep("{I}")"	{yylval.string = (char*)strdup(yytext); return SLEEP;}
"volatile"	{return VOLATILE;}
"nobackup"	{return NOBACKUP;}
"string"	{return STRING;}
"integer"	{return INTEGER;}
"#start "	{return START_STATE;}
"#include \"drone\""	{return INC_DRONE;}
"real"	{return REAL;}
"#States"	{return BEGINT;}
"#EndStates"	{return END;}
"State"	{return STATE_DEC;}
"transition" {eprintf("FOUND TRANSITION\n"); return TRANSITION;}
"print"	{eprintf("print statement\n"); return PRINTF;}
"GLOBAL"	{eprintf("Global variable found\n"); return GLOBALD;}
"drone.left("{I}")"	{eprintf("Left command\n"); char* str1 = (yytext + 11);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_LEFT;}
"drone.right("{I}")"	{eprintf("Right command\n"); char* str1 = (yytext + 12);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_RIGHT;}
"drone.up("{I}")"	{eprintf("Up command\n");char* str1 = (yytext + 9);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1); return DRONE_UP;}
"drone.down("{I}")"	{eprintf("Down command\n"); char* str1 = (yytext + 11);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_DOWN;}
"drone.forward("{I}")"	{eprintf("Forward command\n"); char* str1 = (yytext + 14);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_FORWARD;}
"drone.back("{I}")"	{eprintf("Back command\n"); char* str1 = (yytext + 11);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_BACK;}
"drone.clockwise("{I}")"	{eprintf("Clockwise command\n"); char* str1 = (yytext + 16);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_CLOCKWISE;}
"drone.counterClockwise("{I}")"	{eprintf("Counter Clockwise command\n"); char* str1 = (yytext + 23);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_CCLOCKWISE;}
"drone.flipLeft("{I}")"	{eprintf("Flip Left command\n"); char* str1 = (yytext + 15);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_FLIPLEFT;}
"drone.stopAndLand("{I}")"	{eprintf("S&L command\n"); char* str1 = (yytext + 18);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_SANDL;}
"drone.takeoff("{I}")"	{eprintf("S&L command\n"); char* str1 = (yytext + 13);str1[strlen(str1)-1] = '\0';printf("%s\n",str1);yylval.string = (char*)strdup(str1);return DRONE_TAKEOFF;}
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
