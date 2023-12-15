
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
        struct cmd * root;


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
     TM_TYPE_NAME = 302
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 11 "lang.y"

unsigned int n;
char * i;
struct expr * e;
struct cmd * c;
struct decl_expr_type_list * detl;
struct expr_type_list * etl;
struct var_decl_expr * vde;
void * none;



/* Line 214 of yacc.c  */
#line 180 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 192 "parser.c"

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
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   517

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

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
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    13,    20,    28,    35,    43,
      45,    49,    53,    55,    56,    60,    73,    82,    91,   103,
     110,   112,   114,   116,   118,   122,   127,   135,   144,   146,
     150,   152,   155,   157,   159,   162,   165,   168,   172,   177,
     185,   194,   198,   202,   206,   210,   214,   218,   222,   226,
     230,   234,   238,   242,   246,   248,   251,   256,   260,   264,
     269,   272,   277,   280,   282,   286,   288,   291,   294,   298,
     303,   307,   311,   315,   317,   319,   321
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    50,     9,    50,    -1,    11,
      60,    56,    -1,    12,    13,    56,     5,    51,     6,    -1,
      61,    12,    60,    56,     5,    51,     6,    -1,    12,    14,
      56,     5,    51,     6,    -1,    61,    12,    14,    56,     5,
      51,     6,    -1,    52,    -1,    51,     9,    51,    -1,    11,
      13,    56,    -1,    52,    -1,    -1,    55,    27,    55,    -1,
      15,     7,    55,     7,    16,     5,    51,     6,    17,     5,
      51,     6,    -1,    18,     7,    55,     8,    19,     5,    51,
       6,    -1,    19,     5,    51,     6,    18,     7,    55,     8,
      -1,    20,     7,    52,     9,    55,     9,    52,     8,     5,
      51,     6,    -1,    21,     4,    22,     5,    51,     6,    -1,
      23,    -1,    26,    -1,    24,    -1,    25,    -1,    55,     7,
       8,    -1,    55,     7,    59,     8,    -1,    55,    31,    60,
      58,    33,     7,     8,    -1,    55,    31,    60,    58,    33,
       7,    59,     8,    -1,     3,    -1,     7,    55,     8,    -1,
       4,    -1,    30,    55,    -1,    53,    -1,    54,    -1,    38,
      55,    -1,    39,    55,    -1,    44,    55,    -1,    55,     7,
       8,    -1,    55,     7,    59,     8,    -1,    55,    31,    60,
      58,    33,     7,     8,    -1,    55,    31,    60,    58,    33,
       7,    59,     8,    -1,    55,    39,    55,    -1,    55,    37,
      55,    -1,    55,    38,    55,    -1,    55,    40,    55,    -1,
      55,    41,    55,    -1,    55,    31,    55,    -1,    55,    33,
      55,    -1,    55,    32,    55,    -1,    55,    34,    55,    -1,
      55,    35,    55,    -1,    55,    36,    55,    -1,    55,    29,
      55,    -1,    55,    28,    55,    -1,     4,    -1,    39,    56,
      -1,    56,     7,    57,     8,    -1,    56,     7,     8,    -1,
       7,    56,     8,    -1,    60,    56,    10,    57,    -1,    60,
      56,    -1,    60,    58,    10,    57,    -1,    60,    58,    -1,
      60,    -1,    60,    10,    57,    -1,    39,    -1,     7,     8,
      -1,    39,    58,    -1,    58,     7,     8,    -1,    58,     7,
      57,     8,    -1,     7,    58,     8,    -1,     7,    57,     8,
      -1,    55,    10,    59,    -1,    55,    -1,    13,    -1,    47,
      -1,    46,    31,    45,     4,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    72,    72,    80,    84,    89,    94,    99,   104,   109,
     117,   121,   126,   133,   134,   138,   142,   146,   150,   154,
     158,   162,   166,   170,   174,   178,   182,   186,   194,   198,
     202,   209,   213,   221,   225,   229,   233,   237,   241,   245,
     249,   253,   257,   261,   265,   269,   273,   277,   281,   285,
     289,   293,   297,   301,   308,   312,   316,   320,   324,   331,
     335,   339,   343,   347,   351,   358,   362,   366,   370,   374,
     378,   382,   389,   393,   400,   404,   410
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
  "TM_THEN", "TM_ELSE", "TM_WHILE", "TM_DO", "TM_FOR", "TM_LOCAL", "TM_IN",
  "TM_CONTINUE", "TM_BREAK", "TM_RETURN", "TM_SKIP", "TM_ASGNOP", "TM_OR",
  "TM_AND", "TM_NOT", "TM_LT", "TM_LE", "TM_GT", "TM_GE", "TM_EQ", "TM_NE",
  "TM_PLUS", "TM_MINUS", "TM_MUL", "TM_DIV", "TM_MOD", "TM_UMINUS",
  "TM_DEREF", "TM_ADDROF", "TM_TYPENAME", "TM_TEMPLATE", "TM_TYPE_NAME",
  "$accept", "NT_WHOLE", "NT_GLOBAL_CMD", "NT_LOCAL_CMD", "NT_FOR_CMD",
  "NT_EXPR0", "NT_EXPR1", "NT_EXPR", "NT_NAMED_RIGHT_EXPR",
  "NT_COMPLEX_ARGUMENT_TYPE_LIST", "NT_ANNON_RIGHT_EXPR",
  "NT_EXPR_TYPE_LIST", "NT_TYPE_NAME", "NT_TEMPLATE_HEAD", 0
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    56,    56,    56,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    59,    59,    60,    60,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     3,     6,     7,     6,     7,     1,
       3,     3,     1,     0,     3,    12,     8,     8,    11,     6,
       1,     1,     1,     1,     3,     4,     7,     8,     1,     3,
       1,     2,     1,     1,     2,     2,     2,     3,     4,     7,
       8,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     4,     3,     3,     4,
       2,     4,     2,     1,     3,     1,     2,     2,     3,     4,
       3,     3,     3,     1,     1,     1,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      13,    28,    30,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    22,    23,    21,     0,     0,     0,     0,     0,
       0,     2,     9,    32,    33,     0,     0,     0,    74,    75,
       0,     0,     0,     0,     0,    13,    13,     0,    31,    34,
      35,    36,     0,     1,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,    54,     0,     0,     4,     0,     0,
       0,     0,     0,     0,    12,     0,     0,     0,     3,    37,
      73,     0,    14,    53,    52,    46,     0,    48,    47,    49,
      50,    51,    42,    43,    41,    44,    45,     0,     0,    37,
       0,     0,     0,    55,     0,    13,    13,     0,     0,     0,
       0,    13,     0,    13,     0,     0,    38,     0,    65,     0,
       0,     0,    38,     0,    58,    57,     0,    63,     0,     0,
       0,     0,    11,     0,    10,     0,     0,    76,    72,    66,
       0,     0,    67,     0,     0,    13,    13,     0,    56,     0,
       0,    65,    60,    62,     5,     7,    13,    13,     0,    13,
      19,    71,    70,    68,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,    69,    39,     0,     8,
       6,    39,     0,    59,    61,     0,    16,    17,     0,    40,
      40,     0,    13,    13,     0,     0,    18,    15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    73,    74,    23,    24,    25,   102,   140,
     141,   100,   127,    26
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -83
static const yytype_int16 yypact[] =
{
     133,   -83,   -83,   278,    59,   125,    11,    30,    18,    90,
      24,   -83,   -83,   -83,   -83,   278,   278,   278,   278,    62,
     122,   119,   -83,   -83,   -83,   292,    91,   306,   -83,   -83,
       2,     2,     2,   278,   278,   163,   191,   110,   153,   153,
     153,   153,   130,   -83,   133,   230,   278,   278,   278,    87,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
      61,   240,   -83,    87,   -83,     2,     2,   157,    28,   142,
     427,   341,   172,    10,   -83,   182,   192,   200,   119,   249,
     355,   205,   441,   464,   476,   364,     0,   364,   364,   364,
     364,   364,    79,    79,   153,   153,   153,     2,     2,   -83,
     212,     0,   161,   157,    12,   163,   163,   215,   207,     2,
     214,   163,   278,   163,   203,   278,   283,   103,     0,     3,
     185,   234,   -83,   128,   -83,   -83,   232,     1,    78,    86,
     237,   241,   157,   245,   247,   390,   121,   -83,   -83,   -83,
     255,   243,   257,    16,   260,   163,   163,   266,   -83,    94,
      59,    76,    75,   136,   -83,   -83,   163,   163,   278,   191,
     -83,   -83,   -83,   -83,   269,   258,   167,   190,   268,   -83,
      59,    59,   194,   199,   404,   272,   -83,   295,   279,   -83,
     -83,   -83,   282,   -83,   -83,   276,   -83,   -83,   281,   350,
     -83,   289,   163,   163,   218,   219,   -83,   -83
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   256,   -79,    21,   -83,   -83,    -3,   -28,   -82,
     -22,   -44,    13,   -83
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -28
static const yytype_int16 yytable[] =
{
      27,    81,    67,    68,    69,    64,    64,   117,   149,    65,
     143,   150,    38,    39,    40,    41,   110,    30,    33,   111,
     125,    22,   126,    35,   163,    28,   128,   129,    37,    28,
      70,    71,   134,   105,   136,   104,   144,    34,   103,   118,
     151,    66,    80,    82,    83,    84,    85,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    75,    80,    29,
      85,   164,    86,    29,   119,    22,   166,   167,   169,   120,
     121,   138,    28,    98,    28,    97,   101,   172,   173,   123,
      64,   132,   104,   149,   154,   170,    61,   111,   183,   184,
       1,     2,   155,    42,     3,   111,   142,    36,    64,   152,
      28,   149,   139,    60,    80,   153,    29,    28,    29,   135,
     117,   139,    80,   194,   195,   151,    28,    15,    57,    58,
      59,   178,    43,   103,   182,    16,    17,   160,    44,   142,
     111,    18,    76,   151,    29,   143,     1,     2,    31,    32,
       3,    29,   118,   143,     4,     5,   171,   106,     6,   104,
      29,     7,     8,     9,    10,   174,    11,    12,    13,    14,
      61,   147,    80,    15,   104,    80,     1,     2,   104,   124,
       3,    16,    17,   179,    72,    77,   111,    18,     6,    19,
     175,     7,     8,     9,    10,   109,    11,    12,    13,    14,
     145,   112,   104,    15,     1,     2,   180,   113,     3,   111,
     185,    16,    17,   111,   114,   186,     6,    18,   111,     7,
       8,     9,    10,   116,    11,    12,    13,    14,     1,     2,
     122,    15,     3,    99,   196,   197,   131,   111,   111,    16,
      17,   130,   133,     1,     2,    18,   137,     3,    79,   146,
     148,   104,   156,     1,     2,    15,   157,     3,    99,   -24,
     143,   162,   158,    16,    17,   -24,   111,   -24,   -24,    18,
      15,     1,     2,   161,   143,     3,   177,   165,    16,    17,
      15,     1,     2,   168,    18,     3,   181,   176,    16,    17,
     188,     1,     2,   -25,    18,     3,   192,   189,    15,   -25,
     190,   -25,   -25,   191,   193,   -26,    16,    17,    15,    45,
      78,   -26,    18,   -26,   -26,     0,    16,    17,    15,     0,
       0,     0,    18,    61,    62,     0,    16,    17,     0,    46,
      47,    48,    18,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    47,    48,     0,    63,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    61,   108,
     -27,     0,     0,     0,     0,     0,   -27,     0,   -27,   -27,
       0,     0,    61,     0,     0,   115,     0,     0,     0,    47,
      48,    61,    63,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    47,    48,     0,    63,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    61,     0,   159,
       0,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,    61,   187,     0,     0,     0,     0,     0,    47,    48,
       0,    63,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    47,    48,   107,    63,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,    61,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    63,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    47,
      48,    61,    63,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,    63,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,    63,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59
};

static const yytype_int16 yycheck[] =
{
       3,    45,    30,    31,    32,     4,     4,     7,     7,     7,
       7,    10,    15,    16,    17,    18,     6,     4,     7,     9,
       8,     0,   104,     5,     8,    13,   105,   106,     4,    13,
      33,    34,   111,     5,   113,     7,    33,     7,    66,    39,
      39,    39,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    36,    61,    47,
      63,   143,    49,    47,    86,    44,   145,   146,   150,    97,
      98,   115,    13,    60,    13,    14,    63,   156,   157,   101,
       4,   109,     7,     7,     6,    10,     7,     9,   170,   171,
       3,     4,     6,    31,     7,     9,   118,     7,     4,   127,
      13,     7,     8,    12,   107,   127,    47,    13,    47,   112,
       7,     8,   115,   192,   193,    39,    13,    30,    39,    40,
      41,   165,     0,   151,   168,    38,    39,     6,     9,   151,
       9,    44,    22,    39,    47,     7,     3,     4,    13,    14,
       7,    47,    39,     7,    11,    12,    10,     5,    15,     7,
      47,    18,    19,    20,    21,   158,    23,    24,    25,    26,
       7,    33,   165,    30,     7,   168,     3,     4,     7,     8,
       7,    38,    39,     6,    11,    45,     9,    44,    15,    46,
     159,    18,    19,    20,    21,    13,    23,    24,    25,    26,
       5,     9,     7,    30,     3,     4,     6,     5,     7,     9,
       6,    38,    39,     9,     4,     6,    15,    44,     9,    18,
      19,    20,    21,     8,    23,    24,    25,    26,     3,     4,
       8,    30,     7,     8,     6,     6,    19,     9,     9,    38,
      39,    16,    18,     3,     4,    44,    33,     7,     8,     5,
       8,     7,     5,     3,     4,    30,     5,     7,     8,     0,
       7,     8,     7,    38,    39,     6,     9,     8,     9,    44,
      30,     3,     4,     8,     7,     7,     8,     7,    38,    39,
      30,     3,     4,     7,    44,     7,     8,     8,    38,    39,
       8,     3,     4,     0,    44,     7,     5,     8,    30,     6,
       8,     8,     9,    17,     5,     0,    38,    39,    30,     7,
      44,     6,    44,     8,     9,    -1,    38,    39,    30,    -1,
      -1,    -1,    44,     7,     8,    -1,    38,    39,    -1,    27,
      28,    29,    44,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     7,     8,
       0,    -1,    -1,    -1,    -1,    -1,     6,    -1,     8,     9,
      -1,    -1,     7,    -1,    -1,    10,    -1,    -1,    -1,    28,
      29,     7,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     7,    -1,     9,
      -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    28,    29,     7,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    28,
      29,     7,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     7,    11,    12,    15,    18,    19,    20,
      21,    23,    24,    25,    26,    30,    38,    39,    44,    46,
      49,    50,    52,    53,    54,    55,    61,    55,    13,    47,
      60,    13,    14,     7,     7,     5,     7,     4,    55,    55,
      55,    55,    31,     0,     9,     7,    27,    28,    29,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      12,     7,     8,    31,     4,     7,    39,    56,    56,    56,
      55,    55,    11,    51,    52,    52,    22,    45,    50,     8,
      55,    59,    55,    55,    55,    55,    60,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    14,    60,     8,
      59,    60,    56,    56,     7,     5,     5,     7,     8,    13,
       6,     9,     9,     5,     4,    10,     8,     7,    39,    58,
      56,    56,     8,    58,     8,     8,    57,    60,    51,    51,
      16,    19,    56,    18,    51,    55,    51,    33,    59,     8,
      57,    58,    58,     7,    33,     5,     5,    33,     8,     7,
      10,    39,    56,    58,     6,     6,     5,     5,     7,     9,
       6,     8,     8,     8,    57,     7,    51,    51,     7,    57,
      10,    10,    51,    51,    55,    52,     8,     8,    59,     6,
       6,     8,    59,    57,    57,     6,     6,     8,     8,     8,
       8,    17,     5,     5,    51,    51,     6,     6
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
#line 73 "lang.y"
    {
    (yyval.c) = ((yyvsp[(1) - (1)].c));
    root = (yyval.c);
  ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 81 "lang.y"
    {
    (yyval.c) = (TSeq((yyvsp[(1) - (3)].c),(yyvsp[(3) - (3)].c)));
  ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 85 "lang.y"
    {
    (yyval.c) = (TDecl((yyvsp[(2) - (3)].i), (yyvsp[(3) - (3)].vde)));

  ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 90 "lang.y"
    {
    (yyval.c) = (TFuncDecl("int",(yyvsp[(3) - (6)].vde),(yyvsp[(5) - (6)].c)));

  ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 95 "lang.y"
    {
    (yyval.c) = (TFuncDecl((yyvsp[(3) - (7)].i),(yyvsp[(4) - (7)].vde),(yyvsp[(6) - (7)].c)));
    set_template_typename("");
  ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 100 "lang.y"
    {
    (yyval.c) = (TProcDecl("int",(yyvsp[(3) - (6)].vde),(yyvsp[(5) - (6)].c)));

  ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 105 "lang.y"
    {
    (yyval.c) = (TProcDecl((yyvsp[(3) - (7)].none),(yyvsp[(4) - (7)].vde),(yyvsp[(6) - (7)].c)));
    set_template_typename("");
  ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 110 "lang.y"
    {
    (yyval.c) = (yyvsp[(1) - (1)].c)
  ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 118 "lang.y"
    {
    (yyval.c) = (TSeq((yyvsp[(1) - (3)].c),(yyvsp[(3) - (3)].c)));
  ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 122 "lang.y"
    {
    if(!validate_typename_vde("",(yyvsp[(3) - (3)].vde))) yyerror("Unsupported TYPENAME!!!!");
    (yyval.c) = (TDecl("int", (yyvsp[(3) - (3)].vde)));
  ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 127 "lang.y"
    {
    (yyval.c) = (yyvsp[(1) - (1)].c)
  ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 135 "lang.y"
    {
    (yyval.c) = (TAsgn((yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 139 "lang.y"
    {
    (yyval.c) = (TIf((yyvsp[(3) - (12)].e),(yyvsp[(7) - (12)].c),(yyvsp[(11) - (12)].c)));
  ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 143 "lang.y"
    {
    (yyval.c) = (TWhileDo((yyvsp[(3) - (8)].e),(yyvsp[(7) - (8)].c)));
  ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 147 "lang.y"
    {
    (yyval.c) = (TDoWhile((yyvsp[(3) - (8)].c),(yyvsp[(7) - (8)].e)));
  ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 151 "lang.y"
    {
    (yyval.c) = (TFor((yyvsp[(3) - (11)].c),(yyvsp[(5) - (11)].e),(yyvsp[(7) - (11)].c),(yyvsp[(10) - (11)].c)));
  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 155 "lang.y"
    {
    (yyval.c) = (TLocal((yyvsp[(2) - (6)].i),(yyvsp[(5) - (6)].c)));
  ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 159 "lang.y"
    {
    (yyval.c) = (TContinue());
  ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 163 "lang.y"
    {
    (yyval.c) = (TSkip());
  ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 167 "lang.y"
    {
    (yyval.c) = (TBreak());
  ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 171 "lang.y"
    {
    (yyval.c) = (TReturn());
  ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 175 "lang.y"
    {
    (yyval.c) = (TProc((yyvsp[(1) - (3)].e),TETLNil()));
  ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 179 "lang.y"
    {
    (yyval.c) = (TProc((yyvsp[(1) - (4)].e),(yyvsp[(3) - (4)].etl)));
  ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 183 "lang.y"
    {
    (yyval.c) = (TProc((yyvsp[(1) - (7)].e),TETLNil()));
  ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 187 "lang.y"
    {
    (yyval.c) = (TProc((yyvsp[(1) - (8)].e),(yyvsp[(7) - (8)].etl)));
  ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 195 "lang.y"
    {
    (yyval.e) = (TConst((yyvsp[(1) - (1)].n)));
  ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 199 "lang.y"
    {
    (yyval.e) = ((yyvsp[(2) - (3)].e));
  ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 203 "lang.y"
    {
    (yyval.e) = (TVar((yyvsp[(1) - (1)].i)));
  ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 210 "lang.y"
    {
    (yyval.e) = (TUnOp(T_NOT,(yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 214 "lang.y"
    {
    (yyval.e) = ((yyvsp[(1) - (1)].e));
  ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 222 "lang.y"
    {
    (yyval.e) = ((yyvsp[(1) - (1)].e));
  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 226 "lang.y"
    {
    (yyval.e) = (TUnOp(T_UMINUS,(yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 230 "lang.y"
    {
    (yyval.e) = (TDeref((yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 234 "lang.y"
    {
    (yyval.e) = (TAddrOf((yyvsp[(2) - (2)].e)));
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 238 "lang.y"
    {
    (yyval.e) = (TFunc((yyvsp[(1) - (3)].e),TETLNil()));
  ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 242 "lang.y"
    {
    (yyval.e) = (TFunc((yyvsp[(1) - (4)].e),(yyvsp[(3) - (4)].etl)));
  ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 246 "lang.y"
    {
    (yyval.e) = (TFunc((yyvsp[(1) - (7)].e),TETLNil()));
  ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 250 "lang.y"
    {
    (yyval.e) = (TFunc((yyvsp[(1) - (8)].e),(yyvsp[(7) - (8)].etl)));
  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 254 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MUL,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 258 "lang.y"
    {
    (yyval.e) = (TBinOp(T_PLUS,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 262 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MINUS,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 266 "lang.y"
    {
    (yyval.e) = (TBinOp(T_DIV,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 270 "lang.y"
    {
    (yyval.e) = (TBinOp(T_MOD,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 274 "lang.y"
    {
    (yyval.e) = (TBinOp(T_LT,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 278 "lang.y"
    {
    (yyval.e) = (TBinOp(T_GT,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 282 "lang.y"
    {
    (yyval.e) = (TBinOp(T_LE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 286 "lang.y"
    {
    (yyval.e) = (TBinOp(T_GE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 290 "lang.y"
    {
    (yyval.e) = (TBinOp(T_EQ,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 294 "lang.y"
    {
    (yyval.e) = (TBinOp(T_NE,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 298 "lang.y"
    {
    (yyval.e) = (TBinOp(T_AND,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 302 "lang.y"
    {
    (yyval.e) = (TBinOp(T_OR,(yyvsp[(1) - (3)].e),(yyvsp[(3) - (3)].e)));
  ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 309 "lang.y"
    {
	(yyval.vde) = TIntType((yyvsp[(1) - (1)].i));
  ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 313 "lang.y"
    {
	(yyval.vde) = TPtrType((yyvsp[(2) - (2)].vde));
  ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 317 "lang.y"
    {
    (yyval.vde) = TFuncType((yyvsp[(1) - (4)].vde), (yyvsp[(3) - (4)].detl));
  ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 321 "lang.y"
    {
	(yyval.vde) = TFuncType((yyvsp[(1) - (3)].vde),TDETLNil());
  ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 325 "lang.y"
    {
	(yyval.vde) = ((yyvsp[(2) - (3)].vde));
  ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 332 "lang.y"
    {
	  (yyval.detl) = TDETLCons((yyvsp[(1) - (4)].i), (yyvsp[(2) - (4)].vde), (yyvsp[(4) - (4)].detl)); 
  ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 336 "lang.y"
    {
	  (yyval.detl) = TDETLCons((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].vde), TDETLNil()) ; 
  ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 340 "lang.y"
    {
	  (yyval.detl) = TDETLCons((yyvsp[(1) - (4)].i), (yyvsp[(2) - (4)].vde), (yyvsp[(4) - (4)].detl)); 
  ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 344 "lang.y"
    {
	  (yyval.detl) = TDETLCons((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].vde), TDETLNil()) ; 
  ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 348 "lang.y"
    {
    (yyval.detl) = TDETLCons((yyvsp[(1) - (1)].i), TIntType(""), TDETLNil()) ; 
  ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 352 "lang.y"
    {
    (yyval.detl) = TDETLCons((yyvsp[(1) - (3)].i), TIntType(""), (yyvsp[(3) - (3)].detl)); 
  ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 359 "lang.y"
    {
    (yyval.vde)= TPtrType(TIntType(""));
  ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 363 "lang.y"
    {
    (yyval.vde)= TFuncType(TIntType(""), TDETLNil());
  ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 367 "lang.y"
    {
    (yyval.vde)= TPtrType((yyvsp[(2) - (2)].vde));
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 371 "lang.y"
    {
    (yyval.vde) = TFuncType((yyvsp[(1) - (3)].vde) , TDETLNil());
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 375 "lang.y"
    {
    (yyval.vde) = TFuncType((yyvsp[(1) - (4)].vde) ,(yyvsp[(3) - (4)].detl));
  ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 379 "lang.y"
    {
    (yyval.vde)=((yyvsp[(2) - (3)].vde));
  ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 383 "lang.y"
    {
    (yyval.vde)= TFuncType(TIntType(""), (yyvsp[(2) - (3)].detl));
  ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 390 "lang.y"
    {
	  (yyval.etl) = TETLCons((yyvsp[(1) - (3)].e), (yyvsp[(3) - (3)].etl)); 
  ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 394 "lang.y"
    {
	  (yyval.etl) = TETLCons((yyvsp[(1) - (1)].e), TETLNil()) ; 
  ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 401 "lang.y"
    {
    (yyval.i) = "int";
  ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 405 "lang.y"
    {
    (yyval.i) = (yyvsp[(1) - (1)].none)
  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 411 "lang.y"
    {
    set_template_typename((yyvsp[(4) - (5)].i));
    (yyval.i) = (yyvsp[(4) - (5)].i)
  ;}
    break;



/* Line 1455 of yacc.c  */
#line 2283 "parser.c"
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
#line 416 "lang.y"


void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}

