/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    REALNO = 259,
    ID = 260,
    FOR_EXPRESSION = 261,
    FUNC = 262,
    RELOP = 263,
    PRINTF = 264,
    QUOTE = 265,
    INCLUDE = 266,
    PROGRAM = 267,
    INTEGER = 268,
    REAL = 269,
    VAR = 270,
    BEGINT = 271,
    END = 272,
    STATE_DEC = 273,
    IF = 274,
    FOR = 275,
    THEN = 276,
    ELSE = 277,
    DO = 278,
    ROPAR = 279,
    RCPAR = 280,
    ROBRK = 281,
    RCBRK = 282,
    DOT = 283,
    SEMICOLON = 284,
    COMMA = 285,
    COLON = 286,
    TRANSITION = 287,
    ASSIGNOP = 288,
    AND = 289,
    OR = 290,
    STRING = 291,
    BANG = 292,
    IF_EXPRESSION = 293,
    MULOP = 294,
    ADDOP = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 22 "parser.y" /* yacc.c:1909  */

	int integer;
	double real;
	char* string;
	char character;

#line 102 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
