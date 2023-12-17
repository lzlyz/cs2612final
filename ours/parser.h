
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TM_NAT = 258,
     TM_IDENT = 259,
     TM_LEFT_BRACE = 260,
     TM_RIGHT_BRACE = 261,
     TM_LEFT_PAREN = 262,
     TM_RIGHT_PAREN = 263,
     TM_SEMICOL = 264,
     TM_COMMA = 265,
     TM_VAR = 266,
     TM_FUNC = 267,
     TM_INTTYPE = 268,
     TM_VOID = 269,
     TM_IF = 270,
     TM_THEN = 271,
     TM_ELSE = 272,
     TM_WHILE = 273,
     TM_DO = 274,
     TM_FOR = 275,
     TM_LOCAL = 276,
     TM_IN = 277,
     TM_CONTINUE = 278,
     TM_BREAK = 279,
     TM_RETURN = 280,
     TM_SKIP = 281,
     TM_ASGNOP = 282,
     TM_OR = 283,
     TM_AND = 284,
     TM_NOT = 285,
     TM_LT = 286,
     TM_LE = 287,
     TM_GT = 288,
     TM_GE = 289,
     TM_EQ = 290,
     TM_NE = 291,
     TM_PLUS = 292,
     TM_MINUS = 293,
     TM_MUL = 294,
     TM_DIV = 295,
     TM_MOD = 296,
     TM_UMINUS = 297,
     TM_DEREF = 298,
     TM_ADDROF = 299,
     TM_TYPENAME = 300,
     TM_TEMPLATE = 301,
     TM_TYPE_NAME = 302,
     TM_VAR_NAME = 303,
     TM_PROC_NAME = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 11 "lang.y"

unsigned int n;
char * i;
struct expr * e;
struct cmd * c;
struct decl_expr_type_list * detl;
struct expr_type_list * etl;
struct var_decl_expr * vde;
struct var_type * vt;
void * none;



/* Line 1676 of yacc.c  */
#line 115 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


