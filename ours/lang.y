%{
	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	#include "lib.h"
	void yyerror(char *);
	int yylex(void);
        struct glob_item_list * root;
%}

%union {
unsigned int n;
char * i;
struct type_list * tl;
struct enum_ele_list * eel;
struct left_type * lt;
struct var_decl_expr * vde;
struct glob_item * gi;
struct glob_item_list * gil;
void * none;
}

// Terminals
%token <n> TM_NAT
%token <i> TM_IDENT

%token <none> TM_LEFT_PAREN TM_RIGHT_PAREN
%token <none> TM_RIGHT_BRACKET TM_LEFT_BRACKET
%token <none> TM_LEFT_BRACE TM_RIGHT_BRACE
%token <none> TM_SEMICOL
%token <none> TM_COMMA
%token <none> TM_POINTER
%token <none> TM_STRUCT
%token <none> TM_UNION
%token <none> TM_ENUM
%token <none> TM_TYPEDEF
%token <none> TM_INTTYPE
%token <none> TM_CHARTYPE

// Nonterminals
%type <gil> NT_WHOLE
%type <lt> NT_LEFT_TYPE
%type <tl> NT_FIELD_LIST
%type <tl> NT_ARGUMENT_TYPE_LIST
%type <gil> NT_GLOB_ITEM
%type <gil> NT_GLOB_ITEM_LIST
%type <vde> NT_NAMED_RIGHT_TYPE_EXPR
%type <vde> NT_ANNON_RIGHT_TYPE_EXPR
%type <eel> NT_ENUM_ELE_LIST



// Priority
%nonassoc TM_STRUCT TM_UNION TM_ENUM TM_TYPEDEF TM_INTTYPE TM_CHARTYPE
%right TM_POINTER
%left TM_LEFT_BRACE TM_RIGHT_BRACE
%left TM_LEFT_BRACKET TM_RIGHT_BRACKET
%left TM_LEFT_PAREN TM_RIGHT_PAREN
%right TM_COMMA 
%right TM_SEMICOL
%%
NT_WHOLE:
  NT_GLOB_ITEM_LIST
  {
    $$ = ($1);
    root = $$;
  }
;
NT_LEFT_TYPE:
  TM_INTTYPE
  {
    $$ = TIntType();
  }
| TM_CHARTYPE
 {
    $$ =TCharType();
 }
| TM_IDENT
  {
    $$ =TDefinedType($1);
  }
| TM_STRUCT TM_IDENT TM_LEFT_BRACE NT_FIELD_LIST TM_RIGHT_BRACE
  {
	$$ =  TNewStructType($2, $4);
  }
| TM_STRUCT  TM_LEFT_BRACE NT_FIELD_LIST TM_RIGHT_BRACE
  {
	$$ =  TNewStructType(NULL, $3);
  }
| TM_STRUCT  TM_IDENT TM_LEFT_BRACE  TM_RIGHT_BRACE
  {
	$$ =  TNewStructType($2, TTNil());
  }

| TM_STRUCT  TM_LEFT_BRACE  TM_RIGHT_BRACE
  {
	$$ =  TNewStructType(NULL, TTNil());
  }

| TM_STRUCT TM_IDENT 
  {
	$$ = TStructType($2);
  }

| TM_UNION TM_IDENT TM_LEFT_BRACE NT_FIELD_LIST TM_RIGHT_BRACE
  {
	$$ = TNewUnionType($2, $4);
  }
| TM_UNION  TM_LEFT_BRACE NT_FIELD_LIST TM_RIGHT_BRACE
  {
	$$ = TNewUnionType(NULL, $3);
  }
| TM_UNION TM_IDENT TM_LEFT_BRACE  TM_RIGHT_BRACE
  {
	$$ = TNewUnionType($2, TTNil());
  }
| TM_UNION  TM_LEFT_BRACE  TM_RIGHT_BRACE
  {
	$$ = TNewUnionType(NULL, TTNil());
  }
| TM_UNION TM_IDENT
  {
	$$ = TUnionType($2);
  }

| TM_ENUM TM_IDENT TM_LEFT_BRACE NT_ENUM_ELE_LIST TM_RIGHT_BRACE
  {
	$$ = TNewEnumType($2, $4);
  }
| TM_ENUM  TM_LEFT_BRACE NT_ENUM_ELE_LIST TM_RIGHT_BRACE
  {
	$$ = TNewEnumType(NULL, $3); 
  }

| TM_ENUM TM_IDENT 
  {
	$$ = TEnumType($2); 
  }
;

NT_FIELD_LIST:
  NT_LEFT_TYPE NT_NAMED_RIGHT_TYPE_EXPR TM_SEMICOL
  {
    $$ = TTCons($1, $2, TTNil());
  }
| NT_LEFT_TYPE NT_NAMED_RIGHT_TYPE_EXPR TM_SEMICOL NT_FIELD_LIST
  {
    $$ = TTCons($1, $2, $4);
  }
;
NT_ARGUMENT_TYPE_LIST:
  NT_LEFT_TYPE NT_ANNON_RIGHT_TYPE_EXPR TM_COMMA NT_ARGUMENT_TYPE_LIST
  {
	$$ = TTCons($1, $2, $4); 
  }
|  NT_LEFT_TYPE NT_ANNON_RIGHT_TYPE_EXPR
  {
	$$ = TTCons($1,$2, TTNil()) ; 
  }
| NT_LEFT_TYPE
  {
    $$ = TTCons($1,TOrigType(""), TTNil()) ; 
  }
| NT_LEFT_TYPE TM_COMMA NT_ARGUMENT_TYPE_LIST
  {
    $$ = TTCons($1, TOrigType(""), $3); 
  }
;
NT_ENUM_ELE_LIST:
  TM_IDENT 
  {
    $$ = TECons($1, TENil());
  }
| TM_IDENT TM_COMMA NT_ENUM_ELE_LIST
  {
    $$= TECons($1, $3);
  }
;






NT_NAMED_RIGHT_TYPE_EXPR:
  TM_IDENT
  {
	$$ = TOrigType($1);
  }
| TM_POINTER NT_NAMED_RIGHT_TYPE_EXPR
  {
	$$ = TPtrType($2);
  }
| NT_NAMED_RIGHT_TYPE_EXPR TM_LEFT_BRACKET TM_NAT TM_RIGHT_BRACKET
  {
    $$ = TArrayType($1, $3);
  }
| NT_NAMED_RIGHT_TYPE_EXPR TM_LEFT_PAREN NT_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = TFuncType($1, $3);
  }
| NT_NAMED_RIGHT_TYPE_EXPR TM_LEFT_PAREN  TM_RIGHT_PAREN
  {
	$$ = TFuncType($1,TTNil());
  }
| TM_LEFT_PAREN NT_NAMED_RIGHT_TYPE_EXPR TM_RIGHT_PAREN
  {
	$$ = ($2); 
  }
;

NT_ANNON_RIGHT_TYPE_EXPR:
  TM_POINTER
 {
    $$= TPtrType(TOrigType(""));
 }

| TM_LEFT_BRACKET TM_NAT TM_RIGHT_BRACKET
 {
    $$= TArrayType(TOrigType(""), $2);
 }
| TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$= TFuncType(TOrigType(""), TTNil());
  }
| TM_POINTER NT_ANNON_RIGHT_TYPE_EXPR
 {
    $$=TPtrType($2);
 }
| NT_ANNON_RIGHT_TYPE_EXPR TM_LEFT_BRACKET TM_NAT TM_RIGHT_BRACKET
  {
    $$= TArrayType( $1 ,$3);
  }
| NT_ANNON_RIGHT_TYPE_EXPR TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = TFuncType($1 , TTNil());
  }
| NT_ANNON_RIGHT_TYPE_EXPR TM_LEFT_PAREN NT_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = TFuncType($1 ,$3);
  }
| TM_LEFT_PAREN NT_ANNON_RIGHT_TYPE_EXPR TM_RIGHT_PAREN
  {
    $$=($2);
  }
| TM_LEFT_PAREN NT_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$= TFuncType(TOrigType(""), $2);
  }
;


NT_GLOB_ITEM_LIST:
  NT_GLOB_ITEM
  {
    $$ =TGCons($1, TGNil());
  }
| NT_GLOB_ITEM NT_GLOB_ITEM_LIST
  {
    $$ =TGCons($1, $2);
  }
;

NT_GLOB_ITEM:
  TM_STRUCT TM_IDENT TM_LEFT_BRACE TM_RIGHT_BRACE TM_SEMICOL
 {
    $$=TStructDef($2, TTNil());
 }
|
  TM_STRUCT TM_IDENT TM_LEFT_BRACE NT_FIELD_LIST TM_RIGHT_BRACE TM_SEMICOL
 {
    $$=TStructDef($2,$4);
 }
| TM_STRUCT TM_IDENT TM_SEMICOL
  {
    $$=TStructDecl($2);
  }
| TM_UNION TM_IDENT TM_LEFT_BRACE NT_FIELD_LIST TM_RIGHT_BRACE TM_SEMICOL
  {
    $$=TUnionDef($2 ,$4);
  }
| TM_UNION TM_IDENT TM_LEFT_BRACE TM_RIGHT_BRACE TM_SEMICOL
  {
    $$=TUnionDef($2, TTNil());
  }
| TM_UNION TM_IDENT TM_SEMICOL
  {
    $$=TUnionDecl($2);
  }
| TM_ENUM TM_IDENT TM_SEMICOL
  {
    $$=TEnumDecl($2);
  }
| TM_ENUM TM_IDENT TM_LEFT_BRACE NT_ENUM_ELE_LIST TM_RIGHT_BRACE TM_SEMICOL
  {
    $$= TEnumDef($2, $4);
  }
| TM_TYPEDEF NT_LEFT_TYPE NT_NAMED_RIGHT_TYPE_EXPR TM_SEMICOL
  {
    $$= TTypeDef($2, $3);
  }
| NT_LEFT_TYPE NT_NAMED_RIGHT_TYPE_EXPR TM_SEMICOL
  {
    $$=TVarDef ($1, $2);
  }

;

%%

void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}