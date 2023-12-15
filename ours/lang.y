%{
	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	void yyerror(char *);
	int yylex(void);
        struct cmd * root;
%}

%union {
unsigned int n;
char * i;
struct expr * e;
struct cmd * c;
struct decl_expr_type_list * detl;
struct expr_type_list * etl;
struct var_decl_expr * vde;
void * none;
}

// Terminals
%token <n> TM_NAT
%token <i> TM_IDENT
%token <none> TM_LEFT_BRACE TM_RIGHT_BRACE
%token <none> TM_LEFT_PAREN TM_RIGHT_PAREN
%token <none> TM_SEMICOL TM_COMMA
%token <none> TM_VAR TM_FUNC TM_INTTYPE TM_VOID TM_IF TM_THEN TM_ELSE TM_WHILE TM_DO
%token <none> TM_FOR TM_LOCAL TM_IN TM_CONTINUE TM_BREAK TM_RETURN TM_SKIP
%token <none> TM_ASGNOP
%token <none> TM_OR
%token <none> TM_AND
%token <none> TM_NOT
%token <none> TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%token <none> TM_PLUS TM_MINUS
%token <none> TM_MUL TM_DIV TM_MOD
%token <none> TM_UMINUS TM_DEREF TM_ADDROF
%token <none> TM_TYPENAME TM_TEMPLATE TM_TYPE_NAME // TM_TYPENAME: typename TYPE_NAME: ->given another realisitc type name

// Nonterminals
%type <c> NT_WHOLE
%type <c> NT_GLOBAL_CMD
%type <c> NT_LOCAL_CMD
%type <c> NT_FOR_CMD
%type <e> NT_EXPR0
%type <e> NT_EXPR1
%type <e> NT_EXPR
%type <etl> NT_EXPR_TYPE_LIST
%type <vde> NT_NAMED_RIGHT_EXPR
%type <detl> NT_COMPLEX_ARGUMENT_TYPE_LIST
%type <vde> NT_ANNON_RIGHT_EXPR
%type <i> NT_TYPE_NAME
%type <i> NT_TEMPLATE_HEAD

// Priority
%nonassoc TM_ASGNOP TM_INTTYPE TM_VAR TM_IF TM_THEN TM_ELSE TM_WHILE TM_DO TM_FOR TM_LOCAL TM_IN TM_SKIP TM_CONTINUE TM_BREAK TM_RETURN TM_TEMPLATE TM_TYPENAME  
%left TM_OR
%left TM_AND
%left TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%left TM_PLUS TM_MINUS
%left TM_MUL TM_DIV TM_MOD
%right TM_UMINUS TM_DEREF TM_ADDROF
%left TM_NOT
%left TM_LEFT_BRACE TM_RIGHT_BRACE
%left TM_LEFT_PAREN TM_RIGHT_PAREN
%right TM_COMMA
%right TM_SEMICOL

%%

NT_WHOLE:
  NT_GLOBAL_CMD
  {
    $$ = ($1);
    root = $$;
  }
;

NT_GLOBAL_CMD:
  NT_GLOBAL_CMD TM_SEMICOL NT_GLOBAL_CMD
  {
    $$ = (TSeq($1,$3));
  }
| TM_VAR NT_TYPE_NAME NT_NAMED_RIGHT_EXPR
  {
    $$ = (TDecl($2, $3));

  }
| TM_FUNC TM_INTTYPE NT_NAMED_RIGHT_EXPR TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TFuncDecl("int",$3,$5));

  }
| NT_TEMPLATE_HEAD TM_FUNC NT_TYPE_NAME NT_NAMED_RIGHT_EXPR TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TFuncDecl($3,$4,$6));
    set_template_typename("");
  }
| TM_FUNC TM_VOID NT_NAMED_RIGHT_EXPR TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TProcDecl("int",$3,$5));

  }
| NT_TEMPLATE_HEAD TM_FUNC TM_VOID NT_NAMED_RIGHT_EXPR TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TProcDecl($3,$4,$6));
    set_template_typename("");
  }
| NT_FOR_CMD
  {
    $$ = $1
  }
;

// LOCAL CMD 不能再使用函数定义
NT_LOCAL_CMD:
  NT_LOCAL_CMD TM_SEMICOL NT_LOCAL_CMD
  {
    $$ = (TSeq($1,$3));
  }
| TM_VAR TM_INTTYPE NT_NAMED_RIGHT_EXPR
  {
    if(!validate_typename_vde("",$3)) yyerror("Unsupported TYPENAME!!!!");
    $$ = (TDecl("int", $3));
  }
| NT_FOR_CMD
  {
    $$ = $1
  }
;

// FOR_CMD 应当拒绝掉分号规约 以及任何定义
NT_FOR_CMD:
| NT_EXPR TM_ASGNOP NT_EXPR
  {
    $$ = (TAsgn($1,$3));
  }
| TM_IF TM_LEFT_PAREN NT_EXPR TM_LEFT_PAREN TM_THEN TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE TM_ELSE TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TIf($3,$7,$11));
  }
| TM_WHILE TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN TM_DO TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TWhileDo($3,$7));
  }
| TM_DO TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE TM_WHILE TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = (TDoWhile($3,$7));
  }
| TM_FOR TM_LEFT_PAREN NT_FOR_CMD TM_SEMICOL NT_EXPR TM_SEMICOL NT_FOR_CMD TM_RIGHT_PAREN TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE // Warning, this cmd is not the correct cmd ,it need modify
  {
    $$ = (TFor($3,$5,$7,$10));
  }
| TM_LOCAL TM_IDENT TM_IN TM_LEFT_BRACE NT_LOCAL_CMD TM_RIGHT_BRACE
  {
    $$ = (TLocal($2,$5));
  }
| TM_CONTINUE
  {
    $$ = (TContinue());
  }
| TM_SKIP
  {
    $$ = (TSkip());
  }
| TM_BREAK
  {
    $$ = (TBreak());
  }
| TM_RETURN
  {
    $$ = (TReturn());
  }
| NT_EXPR TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TProc($1,TETLNil()));
  }
| NT_EXPR TM_LEFT_PAREN NT_EXPR_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = (TProc($1,$3));
  }
| NT_EXPR TM_LT NT_TYPE_NAME NT_ANNON_RIGHT_EXPR TM_GT TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TProc($1,TETLNil()));
  }
| NT_EXPR TM_LT NT_TYPE_NAME NT_ANNON_RIGHT_EXPR TM_GT TM_LEFT_PAREN NT_EXPR_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = (TProc($1,$7));
  }
;


NT_EXPR0:
  TM_NAT
  {
    $$ = (TConst($1));
  }
| TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = ($2);
  }
| TM_IDENT
  {
    $$ = (TVar($1));
  }
;

NT_EXPR1:
  TM_NOT NT_EXPR
  {
    $$ = (TUnOp(T_NOT,$2));
  }
| NT_EXPR0
  {
    $$ = ($1);
  }
;


NT_EXPR:
  NT_EXPR1
  {
    $$ = ($1);
  }
| TM_MINUS NT_EXPR %prec TM_UMINUS
  {
    $$ = (TUnOp(T_UMINUS,$2));
  }
| TM_MUL NT_EXPR  %prec TM_DEREF
  {
    $$ = (TDeref($2));
  }
| TM_ADDROF NT_EXPR  %prec TM_ADDROF
  {
    $$ = (TAddrOf($2));
  }
| NT_EXPR TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TFunc($1,TETLNil()));
  }
| NT_EXPR TM_LEFT_PAREN NT_EXPR_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = (TFunc($1,$3));
  }
| NT_EXPR TM_LT NT_TYPE_NAME NT_ANNON_RIGHT_EXPR TM_GT TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TFunc($1,TETLNil()));
  }
| NT_EXPR TM_LT NT_TYPE_NAME NT_ANNON_RIGHT_EXPR TM_GT TM_LEFT_PAREN NT_EXPR_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = (TFunc($1,$7));
  }
| NT_EXPR TM_MUL NT_EXPR
  {
    $$ = (TBinOp(T_MUL,$1,$3));
  }
| NT_EXPR TM_PLUS NT_EXPR
  {
    $$ = (TBinOp(T_PLUS,$1,$3));
  }
| NT_EXPR TM_MINUS NT_EXPR
  {
    $$ = (TBinOp(T_MINUS,$1,$3));
  }
| NT_EXPR TM_DIV NT_EXPR
  {
    $$ = (TBinOp(T_DIV,$1,$3));
  }
| NT_EXPR TM_MOD NT_EXPR
  {
    $$ = (TBinOp(T_MOD,$1,$3));
  }
| NT_EXPR TM_LT NT_EXPR
  {
    $$ = (TBinOp(T_LT,$1,$3));
  }
| NT_EXPR TM_GT NT_EXPR
  {
    $$ = (TBinOp(T_GT,$1,$3));
  }
| NT_EXPR TM_LE NT_EXPR
  {
    $$ = (TBinOp(T_LE,$1,$3));
  }
| NT_EXPR TM_GE NT_EXPR
  {
    $$ = (TBinOp(T_GE,$1,$3));
  }
| NT_EXPR TM_EQ NT_EXPR
  {
    $$ = (TBinOp(T_EQ,$1,$3));
  }
| NT_EXPR TM_NE NT_EXPR
  {
    $$ = (TBinOp(T_NE,$1,$3));
  }
| NT_EXPR TM_AND NT_EXPR
  {
    $$ = (TBinOp(T_AND,$1,$3));
  }
| NT_EXPR TM_OR NT_EXPR
  {
    $$ = (TBinOp(T_OR,$1,$3));
  }
;

NT_NAMED_RIGHT_EXPR:
  TM_IDENT
  {
	$$ = TIntType($1);
  }
| TM_MUL NT_NAMED_RIGHT_EXPR
  {
	$$ = TPtrType($2);
  }
| NT_NAMED_RIGHT_EXPR TM_LEFT_PAREN NT_COMPLEX_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = TFuncType($1, $3);
  }
| NT_NAMED_RIGHT_EXPR TM_LEFT_PAREN  TM_RIGHT_PAREN
  {
	$$ = TFuncType($1,TDETLNil());
  }
| TM_LEFT_PAREN NT_NAMED_RIGHT_EXPR TM_RIGHT_PAREN
  {
	$$ = ($2);
  }
;

NT_COMPLEX_ARGUMENT_TYPE_LIST:
  NT_TYPE_NAME NT_NAMED_RIGHT_EXPR TM_COMMA NT_COMPLEX_ARGUMENT_TYPE_LIST
  {
	  $$ = TDETLCons($1, $2, $4); 
  }
| NT_TYPE_NAME NT_NAMED_RIGHT_EXPR
  {
	  $$ = TDETLCons($1, $2, TDETLNil()) ; 
  }  
| NT_TYPE_NAME NT_ANNON_RIGHT_EXPR TM_COMMA NT_COMPLEX_ARGUMENT_TYPE_LIST
  {
	  $$ = TDETLCons($1, $2, $4); 
  }
| NT_TYPE_NAME NT_ANNON_RIGHT_EXPR
  {
	  $$ = TDETLCons($1, $2, TDETLNil()) ; 
  }
| NT_TYPE_NAME
  {
    $$ = TDETLCons($1, TIntType(""), TDETLNil()) ; 
  }
| NT_TYPE_NAME TM_COMMA NT_COMPLEX_ARGUMENT_TYPE_LIST
  {
    $$ = TDETLCons($1, TIntType(""), $3); 
  }
;

NT_ANNON_RIGHT_EXPR:
  TM_MUL
  {
    $$= TPtrType(TIntType(""));
  }
| TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$= TFuncType(TIntType(""), TDETLNil());
  }
| TM_MUL NT_ANNON_RIGHT_EXPR
  {
    $$= TPtrType($2);
  }
| NT_ANNON_RIGHT_EXPR TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = TFuncType($1 , TDETLNil());
  }
| NT_ANNON_RIGHT_EXPR TM_LEFT_PAREN NT_COMPLEX_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = TFuncType($1 ,$3);
  }
| TM_LEFT_PAREN NT_ANNON_RIGHT_EXPR TM_RIGHT_PAREN
  {
    $$=($2);
  }
| TM_LEFT_PAREN NT_COMPLEX_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$= TFuncType(TIntType(""), $2);
  }
;

NT_EXPR_TYPE_LIST:
  NT_EXPR TM_COMMA NT_EXPR_TYPE_LIST
  {
	  $$ = TETLCons($1, $3); 
  }
| NT_EXPR
  {
	  $$ = TETLCons($1, TETLNil()) ; 
  }
;

NT_TYPE_NAME:
  TM_INTTYPE
  {
    $$ = "int";
  }
| TM_TYPE_NAME
  {
    $$ = $1
  }

NT_TEMPLATE_HEAD:
  TM_TEMPLATE TM_LT TM_TYPENAME TM_IDENT TM_GT
  {
    set_template_typename($4);
    $$ = $4
  }

%%

void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}
