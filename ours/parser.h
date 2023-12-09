/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    TM_NAT = 258,
    TM_IDENT = 259,
    TM_LEFT_BRACE = 260,
    TM_RIGHT_BRACE = 261,
    TM_LEFT_PAREN = 262,
    TM_RIGHT_PAREN = 263,
    TM_SEMICOL = 264,
    TM_COMMA = 265,
    TM_VAR = 266,
    TM_INTTYPE = 267,
    TM_VOID = 268,
    TM_IF = 269,
    TM_THEN = 270,
    TM_ELSE = 271,
    TM_WHILE = 272,
    TM_DO = 273,
    TM_FOR = 274,
    TM_LOCAL = 275,
    TM_IN = 276,
    TM_CONTINUE = 277,
    TM_BREAK = 278,
    TM_RETURN = 279,
    TM_SKIP = 280,
    TM_ASGNOP = 281,
    TM_OR = 282,
    TM_AND = 283,
    TM_NOT = 284,
    TM_LT = 285,
    TM_LE = 286,
    TM_GT = 287,
    TM_GE = 288,
    TM_EQ = 289,
    TM_NE = 290,
    TM_PLUS = 291,
    TM_MINUS = 292,
    TM_MUL = 293,
    TM_DIV = 294,
    TM_MOD = 295,
    TM_UMINUS = 296,
    TM_DEREF = 297,
    TM_ADDROF = 298,
    TM_TYPENAME = 299,
    TM_TEMPLATE = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "lang.y"

unsigned int n;
char * i;
struct expr * e;
struct cmd * c;
struct decl_expr_type_list * detl;
struct expr_type_list * etl;
struct var_decl_expr * vde;
void * none;

#line 114 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
