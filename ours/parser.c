
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "lang.y"

	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	void yyerror(char *);
	int yylex(void);
  struct cmd_list * root;


/* Line 189 of yacc.c  */
#line 84 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     TM_CONTINUE = 276,
     TM_BREAK = 277,
     TM_RETURN = 278,
     TM_SKIP = 279,
     TM_ASGNOP = 280,
     TM_OR = 281,
     TM_AND = 282,
     TM_NOT = 283,
     TM_LT = 284,
     TM_LE = 285,
     TM_GT = 286,
     TM_GE = 287,
     TM_EQ = 288,
     TM_NE = 289,
     TM_PLUS = 290,
     TM_MINUS = 291,
     TM_MUL = 292,
     TM_DIV = 293,
     TM_MOD = 294,
     TM_UMINUS = 295,
     TM_DEREF = 296,
     TM_ADDROF = 297,
     TM_TYPENAME = 298,
     TM_TEMPLATE = 299,
     TM_TEMPLATE_TYPENAME = 300
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 11 "lang.y"

unsigned int n;
char * s;
struct expr * e;
struct cmd * c;
struct cmd_list * cl;
struct var_type_list * vtl;
struct expr_list * el;
struct var_decl_expr * vde;
struct var_type * vt;
enum TypenameType tt;
void * none;



/* Line 214 of yacc.c  */
#line 181 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 193 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   407

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNRULES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    12,    15,    20,    25,    30,
      33,    37,    44,    48,    51,    54,    56,    60,    73,    82,
      91,   103,   105,   107,   109,   111,   114,   118,   123,   125,
     129,   131,   134,   136,   138,   141,   144,   147,   151,   156,
     161,   165,   169,   173,   177,   181,   185,   189,   193,   197,
     201,   205,   209,   213,   215,   218,   223,   227,   231,   235,
     237,   241,   243,   245,   248,   251,   255,   260,   264,   268,
     272,   274,   276,   278,   281,   287,   290,   297,   299,   301,
     303,   305,   308,   311
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    -1,    49,     9,    48,    -1,    49,
       9,    -1,    11,    69,    -1,    61,     5,    50,     6,    -1,
      63,     5,    50,     6,    -1,    64,     5,    50,     6,    -1,
      12,    69,    -1,    62,    12,    69,    -1,    12,    14,     4,
       7,    57,     8,    -1,    51,     9,    50,    -1,    51,     9,
      -1,    11,    69,    -1,    52,    -1,    55,    25,    55,    -1,
      68,     7,    55,     8,    16,     5,    50,     6,    17,     5,
      50,     6,    -1,    66,     7,    55,     8,    19,     5,    50,
       6,    -1,    67,     5,    50,     6,    18,     7,    55,     8,
      -1,    65,     7,    52,     9,    55,     9,    52,     8,     5,
      50,     6,    -1,    21,    -1,    24,    -1,    22,    -1,    23,
      -1,    23,    55,    -1,    55,     7,     8,    -1,    55,     7,
      59,     8,    -1,     3,    -1,     7,    55,     8,    -1,     4,
      -1,    28,    55,    -1,    53,    -1,    54,    -1,    36,    55,
      -1,    37,    55,    -1,    42,    55,    -1,    55,     7,     8,
      -1,    55,     7,    59,     8,    -1,    55,    29,    70,    31,
      -1,    55,    37,    55,    -1,    55,    35,    55,    -1,    55,
      36,    55,    -1,    55,    38,    55,    -1,    55,    39,    55,
      -1,    55,    29,    55,    -1,    55,    31,    55,    -1,    55,
      30,    55,    -1,    55,    32,    55,    -1,    55,    33,    55,
      -1,    55,    34,    55,    -1,    55,    27,    55,    -1,    55,
      26,    55,    -1,     4,    -1,    37,    56,    -1,    56,     7,
      57,     8,    -1,    56,     7,     8,    -1,     7,    56,     8,
      -1,    69,    10,    57,    -1,    69,    -1,    70,    10,    57,
      -1,    70,    -1,    37,    -1,     7,     8,    -1,    37,    58,
      -1,    58,     7,     8,    -1,    58,     7,    57,     8,    -1,
       7,    58,     8,    -1,     7,    57,     8,    -1,    55,    10,
      59,    -1,    55,    -1,    13,    -1,    45,    -1,    12,    69,
      -1,    44,    29,    43,     4,    31,    -1,    62,    61,    -1,
      12,    14,     4,     7,    57,     8,    -1,    20,    -1,    18,
      -1,    19,    -1,    15,    -1,    60,    56,    -1,    60,    58,
      -1,    60,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   108,   112,   119,   124,   131,   139,   145,
     150,   157,   177,   181,   189,   194,   202,   206,   211,   216,
     221,   226,   230,   234,   238,   242,   246,   250,   258,   262,
     266,   273,   277,   285,   289,   293,   297,   301,   305,   309,
     313,   317,   321,   325,   329,   333,   337,   341,   345,   349,
     353,   357,   361,   368,   372,   376,   380,   384,   391,   395,
     399,   403,   410,   414,   418,   422,   426,   430,   434,   441,
     445,   452,   456,   463,   480,   489,   498,   511,   518,   525,
     532,   539,   546,   550
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TM_NAT", "TM_IDENT", "TM_LEFT_BRACE",
  "TM_RIGHT_BRACE", "TM_LEFT_PAREN", "TM_RIGHT_PAREN", "TM_SEMICOL",
  "TM_COMMA", "TM_VAR", "TM_FUNC", "TM_INTTYPE", "TM_VOID", "TM_IF",
  "TM_THEN", "TM_ELSE", "TM_WHILE", "TM_DO", "TM_FOR", "TM_CONTINUE",
  "TM_BREAK", "TM_RETURN", "TM_SKIP", "TM_ASGNOP", "TM_OR", "TM_AND",
  "TM_NOT", "TM_LT", "TM_LE", "TM_GT", "TM_GE", "TM_EQ", "TM_NE",
  "TM_PLUS", "TM_MINUS", "TM_MUL", "TM_DIV", "TM_MOD", "TM_UMINUS",
  "TM_DEREF", "TM_ADDROF", "TM_TYPENAME", "TM_TEMPLATE",
  "TM_TEMPLATE_TYPENAME", "$accept", "NT_WHOLE", "NT_GLOBAL_CMD_LIST",
  "NT_GLOBAL_CMD", "NT_LOCAL_CMD_LIST", "NT_LOCAL_CMD", "NT_FOR_CMD",
  "NT_EXPR0", "NT_EXPR1", "NT_EXPR", "NT_NAMED_RIGHT_EXPR",
  "NT_COMPLEX_ARGUMENT_TYPE_LIST", "NT_ANNON_RIGHT_EXPR",
  "NT_EXPR_TYPE_LIST", "NT_TYPE_NAME", "NT_FUNC_HEAD", "NT_TEMPLATE_HEAD",
  "NT_TEMPLATE_FUNC_HEAD", "NT_PROC_HEAD", "NT_FOR_HEAD", "NT_WHILE_HEAD",
  "NT_DO_HEAD", "NT_IF_HEAD", "NT_NAMED_HEAD", "NT_ANNON_HEAD", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    56,    56,    57,    57,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     2,     2,     4,     4,     4,     2,
       3,     6,     3,     2,     2,     1,     3,    12,     8,     8,
      11,     1,     1,     1,     1,     2,     3,     4,     1,     3,
       1,     2,     1,     1,     2,     2,     2,     3,     4,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     4,     3,     3,     3,     1,
       3,     1,     1,     2,     2,     3,     4,     3,     3,     3,
       1,     1,     1,     2,     5,     2,     6,     1,     1,     1,
       1,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     0,     0,     0,     0,
       0,    71,    72,     0,     5,     0,     9,     0,     1,     4,
       0,     0,    75,     0,     0,    53,     0,     0,    81,     0,
       0,     3,    28,    30,     0,     0,    80,    78,    79,    77,
      21,    23,    24,    22,     0,     0,     0,     0,     0,     0,
      15,    32,    33,     0,     0,     0,     0,     0,    10,     0,
       0,     0,    54,     0,     0,     0,     0,    14,    25,    31,
      34,    35,    36,     6,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,    57,    56,     0,    83,
      59,    61,     0,    74,     0,    29,    12,    37,    70,     0,
      16,    52,    51,    45,    83,     0,    47,    46,    48,    49,
      50,    41,    42,    40,    43,    44,     0,     0,     0,     0,
      55,     0,    62,    82,     0,     0,    11,    37,     0,     0,
      38,     0,    62,    39,     0,     0,     0,     0,    63,     0,
       0,    64,     0,    58,    60,    38,    69,     0,     0,     0,
       0,    68,    67,    65,     0,     0,     0,     0,     0,    66,
       0,     0,     0,     0,     0,    18,    19,     0,     0,     0,
       0,     0,    20,     0,    17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    48,    49,    50,    51,    52,    53,
      28,   149,   133,   109,    99,     7,     8,     9,    10,    54,
      55,    56,    57,   100,   101
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int16 yypact[] =
{
      85,    33,    92,   -20,    19,   -93,    13,    37,    41,    89,
      95,   -93,   -93,    11,   -93,    78,    97,    61,   -93,    85,
     129,    33,   -93,   129,   129,   -93,    11,    11,   102,   106,
     113,   -93,   -93,   -93,   179,    33,   -93,   -93,   -93,   -93,
     -93,   -93,   179,   -93,   179,   179,   179,   179,    93,   115,
     -93,   -93,   -93,   193,   118,   121,   117,   123,    97,   135,
     136,    21,   102,    26,    33,   125,   226,   -93,   355,   147,
     147,   147,   147,   -93,   129,    84,   179,   179,   179,     7,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     157,   179,   129,   179,   -93,   -93,   -93,   -93,   154,    94,
     153,   159,   162,   -93,   131,   -93,   -93,    22,   240,   176,
     355,   368,   206,   167,    73,   158,   167,   167,   167,   167,
     167,    77,    77,   147,   147,   147,   181,   273,   185,   287,
     -93,    82,    94,   188,    33,    33,   187,   -93,   200,   179,
      24,    66,    73,   -93,   179,   177,   183,   194,   -93,   201,
      30,   188,    32,   -93,   -93,   -93,   -93,   320,   207,   204,
     209,   -93,   -93,   -93,   238,   157,   129,   179,   129,   -93,
     241,   211,   334,   242,   246,   -93,   -93,   237,   129,   263,
     276,   129,   -93,   277,   -93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   265,   -93,   -23,   -93,   -84,   -93,   -93,   -21,
     -24,   -59,    56,   -92,     6,   278,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,    15,   208
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -77
static const yytype_int16 yytable[] =
{
      59,    60,    61,    62,    98,   102,   126,    13,    13,    17,
      32,    33,   138,    66,    34,    25,    14,    16,    26,    18,
      11,    68,    19,    69,    70,    71,    72,    13,    63,    96,
     -26,   -26,   -27,   -27,    97,    44,    58,   152,   162,    11,
     163,    13,    20,    45,    46,    11,    11,   156,    27,    47,
      67,   106,    12,    21,   108,   110,   111,   112,   113,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   128,
     127,    12,   129,   141,   148,   153,   154,    12,    12,    11,
     141,   170,    29,   108,   104,   114,    25,    32,    33,   131,
     148,    34,   107,   164,    23,    11,     1,     2,    25,    73,
      24,   131,   -73,   142,    30,    11,    15,    61,    62,    63,
     142,    12,    44,    64,    87,    88,    89,    65,   108,   132,
      45,    46,    92,   157,    74,    90,    47,    12,    91,     3,
      93,   132,    32,    33,    32,    33,    34,    12,    34,   137,
      35,    94,    95,   171,    36,   173,   172,    37,    38,    39,
      40,    41,    42,    43,   104,   180,   103,    44,   183,    44,
      32,    33,   130,   134,    34,    45,    46,    45,    46,   135,
     136,    47,    36,    47,   104,    37,    38,    39,    40,    41,
      42,    43,    32,    33,   140,    44,    34,   150,   151,   143,
     144,   146,   -76,    45,    46,   152,   158,   150,   151,    47,
      75,   159,    85,    86,    87,    88,    89,    44,   155,   161,
     160,   167,   166,   104,   168,    45,    46,   175,    76,    77,
      78,    47,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   104,   105,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   169,   104,   177,   174,
     139,   178,    77,    78,   179,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    77,    78,   181,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     104,   145,   182,   184,    31,     0,    22,   115,     0,     0,
       0,     0,     0,     0,   104,   147,     0,     0,     0,    77,
      78,     0,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    77,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   104,     0,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   176,     0,     0,     0,    77,    78,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      77,    78,   104,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,   104,     0,     0,     0,     0,
       0,    77,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    78,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89
};

static const yytype_int16 yycheck[] =
{
      23,    24,    26,    27,    63,    64,    90,     1,     2,    29,
       3,     4,   104,    34,     7,     4,     1,     2,     7,     0,
      13,    42,     9,    44,    45,    46,    47,    21,     7,     8,
       8,     9,     8,     9,     8,    28,    21,     7,     8,    13,
       8,    35,     5,    36,    37,    13,    13,   139,    37,    42,
      35,    74,    45,    12,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    92,
      91,    45,    93,     7,     8,   134,   135,    45,    45,    13,
       7,   165,     4,   104,     7,    79,     4,     3,     4,     7,
       8,     7,     8,   152,     5,    13,    11,    12,     4,     6,
       5,     7,     5,    37,    43,    13,    14,   131,   132,     7,
      37,    45,    28,     7,    37,    38,    39,     4,   139,    37,
      36,    37,     5,   144,     9,     7,    42,    45,     7,    44,
       7,    37,     3,     4,     3,     4,     7,    45,     7,     8,
      11,     6,     6,   166,    15,   168,   167,    18,    19,    20,
      21,    22,    23,    24,     7,   178,    31,    28,   181,    28,
       3,     4,     8,    10,     7,    36,    37,    36,    37,    10,
       8,    42,    15,    42,     7,    18,    19,    20,    21,    22,
      23,    24,     3,     4,     8,    28,     7,   131,   132,    31,
       9,     6,     5,    36,    37,     7,    19,   141,   142,    42,
       7,    18,    35,    36,    37,    38,    39,    28,     8,     8,
      16,     7,     5,     7,     5,    36,    37,     6,    25,    26,
      27,    42,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     7,     8,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     8,     7,     6,     8,
      10,     5,    26,    27,    17,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    26,    27,     5,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       7,     8,     6,     6,    19,    -1,     8,    79,    -1,    -1,
      -1,    -1,    -1,    -1,     7,     8,    -1,    -1,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     7,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     7,     8,    -1,    -1,    -1,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      26,    27,     7,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,     7,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    27,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    44,    47,    48,    49,    61,    62,    63,
      64,    13,    45,    60,    69,    14,    69,    29,     0,     9,
       5,    12,    61,     5,     5,     4,     7,    37,    56,     4,
      43,    48,     3,     4,     7,    11,    15,    18,    19,    20,
      21,    22,    23,    24,    28,    36,    37,    42,    50,    51,
      52,    53,    54,    55,    65,    66,    67,    68,    69,    50,
      50,    56,    56,     7,     7,     4,    55,    69,    55,    55,
      55,    55,    55,     6,     9,     7,    25,    26,    27,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       7,     7,     5,     7,     6,     6,     8,     8,    57,    60,
      69,    70,    57,    31,     7,     8,    50,     8,    55,    59,
      55,    55,    55,    55,    60,    70,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    52,    55,    50,    55,
       8,     7,    37,    58,    10,    10,     8,     8,    59,    10,
       8,     7,    37,    31,     9,     8,     6,     8,     8,    57,
      58,    58,     7,    57,    57,     8,    59,    55,    19,    18,
      16,     8,     8,     8,    57,     9,     5,     7,     5,     8,
      52,    50,    55,    50,     8,     6,     8,     6,     5,    17,
      50,     5,     6,    50,     6
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 101 "lang.y"
    {
    (yyval.cl) = ((yyvsp[(1) - (1)].cl));
    root = (yyval.cl);
  ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 109 "lang.y"
    {
    (yyval.cl) = TCLCons((yyvsp[(1) - (3)].c), (yyvsp[(3) - (3)].cl));
  ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 113 "lang.y"
    {
    (yyval.cl) = TCLCons((yyvsp[(1) - (2)].c), TCLNil());
  ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 120 "lang.y"
    {
    (yyval.c) = (TDecl((yyvsp[(2) - (2)].vt)));
    vtable_add(get_now_vtable(), (yyvsp[(2) - (2)].vt));
  ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 125 "lang.y"
    {
    (yyval.c) = (TFuncDecl((yyvsp[(1) - (4)].vt)));
    vtable_add_cmd_list(get_global_vtable(), (yyvsp[(1) - (4)].vt), (yyvsp[(3) - (4)].cl));
    set_function_returntype(NULL);
    clear_now_vtable();
  ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 132 "lang.y"
    {
    (yyval.c) = (TFuncDecl((yyvsp[(1) - (4)].vt)));
    vtable_add_cmd_list(get_global_vtable(), (yyvsp[(1) - (4)].vt), (yyvsp[(3) - (4)].cl));
    set_template_typename(NULL);
    set_function_returntype(NULL);
    clear_now_vtable();
  ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 140 "lang.y"
    {
    (yyval.c) = (TProcDecl((yyvsp[(1) - (4)].vt)));
    vtable_add_cmd_list(get_global_vtable(), (yyvsp[(1) - (4)].vt), (yyvsp[(3) - (4)].cl));
    clear_now_vtable();
  ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 146 "lang.y"
    {
    function_type_test_in_decl((yyvsp[(2) - (2)].vt));
    (yyval.c) = TFuncProtoDecl((yyvsp[(2) - (2)].vt));
  ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 151 "lang.y"
    {
    function_type_test_in_decl((yyvsp[(3) - (3)].vt));
    set_function_template_typename((yyvsp[(3) - (3)].vt),(yyvsp[(1) - (3)].s));
    (yyval.c) = TFuncProtoDecl((yyvsp[(3) - (3)].vt));
    set_template_typename(NULL);
  ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 158 "lang.y"
    {
    (yyval.c) = TProcProtoDecl(TVarType(T_TYPENAME_VOID, TFuncType(TIntType((yyvsp[(3) - (6)].s)), (yyvsp[(5) - (6)].vtl))));
  ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 178 "lang.y"
    {
    (yyval.cl) = TCLCons((yyvsp[(1) - (3)].c), (yyvsp[(3) - (3)].cl));
  ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 182 "lang.y"
    {
    (yyval.cl) = TCLCons((yyvsp[(1) - (2)].c), TCLNil());
  ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 190 "lang.y"
    {
    (yyval.c) = (TDecl((yyvsp[(2) - (2)].vt)));
    vtable_add(get_now_vtable(), (yyvsp[(2) - (2)].vt));
  ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 195 "lang.y"
    {
    (yyval.c) = (yyvsp[(1) - (1)].c)
  ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 203 "lang.y"
    {
    (yyval.c) = (TAsgn((yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 207 "lang.y"
    {
    (yyval.c) = (TIf((yyvsp[(3) - (12)].e),(yyvsp[(7) - (12)].cl),(yyvsp[(11) - (12)].cl)));
    clear_now_vtable();
  ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 212 "lang.y"
    {
    (yyval.c) = (TWhileDo((yyvsp[(3) - (8)].e),(yyvsp[(7) - (8)].cl)));
    clear_now_vtable();
  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 217 "lang.y"
    {
    (yyval.c) = (TDoWhile((yyvsp[(3) - (8)].cl),(yyvsp[(7) - (8)].e)));
    clear_now_vtable();
  ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 222 "lang.y"
    {
    (yyval.c) = (TFor((yyvsp[(3) - (11)].c),(yyvsp[(5) - (11)].e),(yyvsp[(7) - (11)].c),(yyvsp[(10) - (11)].cl)));
    clear_now_vtable();
  ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 227 "lang.y"
    {
    (yyval.c) = (TContinue());
  ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 231 "lang.y"
    {
    (yyval.c) = (TSkip());
  ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 235 "lang.y"
    {
    (yyval.c) = (TBreak());
  ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 239 "lang.y"
    {
    (yyval.c) = (TReturn(NULL));
  ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 243 "lang.y"
    {
    (yyval.c) = (TReturn((yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 247 "lang.y"
    {
    (yyval.c) = (TProc((yyvsp[(1) - (3)].e),TELNil()));
  ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 251 "lang.y"
    {
    (yyval.c) = (TProc((yyvsp[(1) - (4)].e),(yyvsp[(3) - (4)].el)));
  ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 259 "lang.y"
    {
    (yyval.e) = (TConst((yyvsp[(1) - (1)].n)));
  ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 263 "lang.y"
    {
    (yyval.e) = ((yyvsp[(2) - (3)].e));
  ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 267 "lang.y"
    {
    (yyval.e) = (TVar((yyvsp[(1) - (1)].s)));
  ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 274 "lang.y"
    {
    (yyval.e) = (TUnOp(T_NOT,(yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 278 "lang.y"
    {
    (yyval.e) = ((yyvsp[(1) - (1)].e));
  ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 286 "lang.y"
    {
    (yyval.e) = ((yyvsp[(1) - (1)].e));
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 290 "lang.y"
    {
    (yyval.e) = (TUnOp(T_UMINUS,(yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 294 "lang.y"
    {
    (yyval.e) = (TDeref((yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 298 "lang.y"
    {
    (yyval.e) = (TAddrOf((yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 302 "lang.y"
    {
    (yyval.e) = (TFunc((yyvsp[(1) - (3)].e),TELNil()));
  ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 306 "lang.y"
    {
    (yyval.e) = (TFunc((yyvsp[(1) - (4)].e),(yyvsp[(3) - (4)].el)));
  ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 310 "lang.y"
    {
    (yyval.e) = (TInstance((yyvsp[(1) - (4)].e),(yyvsp[(3) - (4)].vt)));
  ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 314 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MUL,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 318 "lang.y"
    {
    (yyval.e) = (TBinOp(T_PLUS,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 322 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MINUS,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 326 "lang.y"
    {
    (yyval.e) = (TBinOp(T_DIV,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 330 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MOD,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 334 "lang.y"
    {
    (yyval.e) = (TBinOp(T_LT,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 338 "lang.y"
    {
    (yyval.e) = (TBinOp(T_GT,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 342 "lang.y"
    {
    (yyval.e) = (TBinOp(T_LE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 346 "lang.y"
    {
    (yyval.e) = (TBinOp(T_GE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 350 "lang.y"
    {
    (yyval.e) = (TBinOp(T_EQ,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 354 "lang.y"
    {
    (yyval.e) = (TBinOp(T_NE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 358 "lang.y"
    {
    (yyval.e) = (TBinOp(T_AND,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 362 "lang.y"
    {
    (yyval.e) = (TBinOp(T_OR,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 369 "lang.y"
    {
	(yyval.vde) = TIntType((yyvsp[(1) - (1)].s));
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 373 "lang.y"
    {
	(yyval.vde) = TPtrType((yyvsp[(2) - (2)].vde));
  ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 377 "lang.y"
    {
  (yyval.vde) = TFuncType((yyvsp[(1) - (4)].vde), (yyvsp[(3) - (4)].vtl));
  ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 381 "lang.y"
    {
	(yyval.vde) = TFuncType((yyvsp[(1) - (3)].vde),TVTLNil());
  ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 385 "lang.y"
    {
	(yyval.vde) = ((yyvsp[(2) - (3)].vde));
  ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 392 "lang.y"
    {
	  (yyval.vtl) = TVTLCons((yyvsp[(1) - (3)].vt), (yyvsp[(3) - (3)].vtl)); 
  ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 396 "lang.y"
    {
	  (yyval.vtl) = TVTLCons((yyvsp[(1) - (1)].vt), TVTLNil()) ; 
  ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 400 "lang.y"
    {
	  (yyval.vtl) = TVTLCons((yyvsp[(1) - (3)].vt), (yyvsp[(3) - (3)].vtl)); 
  ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 404 "lang.y"
    {
	  (yyval.vtl) = TVTLCons((yyvsp[(1) - (1)].vt), TVTLNil()) ; 
  ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 411 "lang.y"
    {
    (yyval.vde)= TPtrType(TIntType(""));
  ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 415 "lang.y"
    {
    (yyval.vde)= TFuncType(TIntType(""), TVTLNil());
  ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 419 "lang.y"
    {
    (yyval.vde)= TPtrType((yyvsp[(2) - (2)].vde));
  ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 423 "lang.y"
    {
    (yyval.vde) = TFuncType((yyvsp[(1) - (3)].vde) , TVTLNil());
  ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 427 "lang.y"
    {
    (yyval.vde) = TFuncType((yyvsp[(1) - (4)].vde) ,(yyvsp[(3) - (4)].vtl));
  ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 431 "lang.y"
    {
    (yyval.vde)=((yyvsp[(2) - (3)].vde));
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 435 "lang.y"
    {
    (yyval.vde)= TFuncType(TIntType(""), (yyvsp[(2) - (3)].vtl));
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 442 "lang.y"
    {
	  (yyval.el) = TELCons((yyvsp[(1) - (3)].e), (yyvsp[(3) - (3)].el)); 
  ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 446 "lang.y"
    {
	  (yyval.el) = TELCons((yyvsp[(1) - (1)].e), TELNil()) ; 
  ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 453 "lang.y"
    {
    (yyval.tt) = T_TYPENAME_INT;
  ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 457 "lang.y"
    {
    (yyval.tt) = T_TYPENAME_TEMPLATE;
  ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 464 "lang.y"
    {
    function_type_test_in_decl((yyvsp[(2) - (2)].vt));
    func_decl_test((yyvsp[(2) - (2)].vt));

    (yyval.vt) = (yyvsp[(2) - (2)].vt);
    vtable_add(get_global_vtable(), (yyvsp[(2) - (2)].vt)); // global_vtable

    set_function_returntype(TFuncReturnType((yyvsp[(2) - (2)].vt)));

    init_new_now_vtable();
    vtable_add(get_now_vtable(), (yyvsp[(2) - (2)].vt));
    vtable_add_list(get_now_vtable(),get_vde_vtl((yyvsp[(2) - (2)].vt)->vde));
  ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 481 "lang.y"
    {
    set_template_typename((yyvsp[(4) - (5)].s));
    (yyval.s) = (yyvsp[(4) - (5)].s);
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 490 "lang.y"
    {
    // vtable_add_template(get_global_vtable(),$2,$1);
    set_function_template_typename((yyvsp[(2) - (2)].vt),(yyvsp[(1) - (2)].s));
    (yyval.vt) = (yyvsp[(2) - (2)].vt);
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 499 "lang.y"
    {
    (yyval.vt) = TVarType(T_TYPENAME_VOID, TFuncType(TIntType((yyvsp[(3) - (6)].s)), (yyvsp[(5) - (6)].vtl)));
    proc_decl_test((yyval.vt));
    vtable_add(get_global_vtable(), (yyval.vt));

    init_new_now_vtable();
    vtable_add(get_now_vtable(), (yyval.vt));
    vtable_add_list(get_now_vtable(),(yyvsp[(5) - (6)].vtl));
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 512 "lang.y"
    {
    init_new_now_vtable();
  ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 519 "lang.y"
    {
    init_new_now_vtable();
  ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 526 "lang.y"
    {
    init_new_now_vtable();
  ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 533 "lang.y"
    {
    init_new_now_vtable();
  ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 540 "lang.y"
    {
    (yyval.vt) = TVarType((yyvsp[(1) - (2)].tt),(yyvsp[(2) - (2)].vde));
  ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 547 "lang.y"
    {
    (yyval.vt) = TVarType((yyvsp[(1) - (2)].tt),(yyvsp[(2) - (2)].vde));
  ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 551 "lang.y"
    {
    (yyval.vt) = TVarType((yyvsp[(1) - (1)].tt),TIntType(""));
  ;}
    break;



/* Line 1455 of yacc.c  */
#line 2370 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 556 "lang.y"


/* ----------------------------------
            Other Functions
   ---------------------------------- */

void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}

