%{
	// this part is copied to the beginning of the parser 
	#include <stdio.h>
	#include "lang.h"
	#include "lexer.h"
	void yyerror(char *);
	int yylex(void);
  struct cmd_list * root;
%}

%union {
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
}

/* ----------------------------------
              Terminals
   ---------------------------------- */
%token <n> TM_NAT
%token <s> TM_IDENT
%token <none> TM_LEFT_BRACE TM_RIGHT_BRACE
%token <none> TM_LEFT_PAREN TM_RIGHT_PAREN
%token <none> TM_SEMICOL TM_COMMA
%token <none> TM_VAR TM_FUNC TM_INTTYPE TM_VOID TM_IF TM_THEN TM_ELSE TM_WHILE TM_DO
%token <none> TM_FOR TM_CONTINUE TM_BREAK TM_RETURN TM_SKIP
%token <none> TM_ASGNOP
%token <none> TM_OR
%token <none> TM_AND
%token <none> TM_NOT
%token <none> TM_LT TM_LE TM_GT TM_GE TM_EQ TM_NE
%token <none> TM_PLUS TM_MINUS
%token <none> TM_MUL TM_DIV TM_MOD
%token <none> TM_UMINUS TM_DEREF TM_ADDROF

// TM_TYPENAME is keyword "typename", TM_TEMPLATE_TYPENAME is the left type name used in declaration.
%token <none> TM_TYPENAME 
%token <none> TM_TEMPLATE TM_TEMPLATE_TYPENAME

/* ----------------------------------
              Nonterminals
   ---------------------------------- */

%type <cl> NT_WHOLE

// GLOBAL_CMD and LOCAL_CMD are easy to understand. FOR_CMD is used for "for".
%type <c> NT_GLOBAL_CMD NT_FOR_CMD NT_LOCAL_CMD

%type <cl> NT_GLOBAL_CMD_LIST NT_LOCAL_CMD_LIST

// EXPR0 EXPR1 are used for avoiding conflicts.
%type <e> NT_EXPR NT_EXPR1 NT_EXPR0
%type <el> NT_EXPR_TYPE_LIST
%type <vde> NT_NAMED_RIGHT_EXPR NT_ANNON_RIGHT_EXPR

// Complex argument type list allows NT_NAMED_RIGHT_EXPR and NT_ANNON_RIGHT_EXPR
%type <vtl> NT_COMPLEX_ARGUMENT_TYPE_LIST

// NT_TYPE_NAME is used for product INT and template type names.
%type <tt> NT_TYPE_NAME

// Nonterminals suffixed with "HEAD" are used to allocate a local variable table,
// confirm the return type of functions and confirm the template type name of 
// polymorphic functions before it starts reading commands.
%type <s> NT_TEMPLATE_HEAD
%type <vt> NT_FUNC_HEAD NT_PROC_HEAD NT_NAMED_HEAD NT_ANNON_HEAD NT_TEMPLATE_FUNC_HEAD
%type <none> NT_FOR_HEAD NT_WHILE_HEAD NT_DO_HEAD NT_IF_HEAD

/* ----------------------------------
                Priority 
   ---------------------------------- */
%nonassoc TM_ASGNOP TM_INTTYPE TM_VAR TM_IF TM_THEN TM_ELSE TM_WHILE TM_DO TM_FOR TM_SKIP TM_CONTINUE TM_BREAK TM_RETURN TM_TEMPLATE TM_TYPENAME  
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


/* ----------------------------------
          Production Rules
   ---------------------------------- */
%%

NT_WHOLE:
  NT_GLOBAL_CMD_LIST
  {
    $$ = ($1);
    root = $$;
  }
;

NT_GLOBAL_CMD_LIST:
  NT_GLOBAL_CMD TM_SEMICOL NT_GLOBAL_CMD_LIST
  {
    $$ = TCLCons($1, $3);
  }
| NT_GLOBAL_CMD TM_SEMICOL
  {
    $$ = TCLCons($1, TCLNil());
  }
;

NT_GLOBAL_CMD:
  TM_VAR NT_NAMED_HEAD
  {
    $$ = (TDecl($2));
    vtable_add(get_now_vtable(), $2);
  }
| NT_FUNC_HEAD TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    $$ = (TFuncDecl($1));
    vtable_add_cmd_list(get_global_vtable(), $1, $3);
    set_function_returntype(NULL);
    clear_now_vtable();
  }
| NT_TEMPLATE_FUNC_HEAD TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    $$ = (TFuncDecl($1));
    vtable_add_cmd_list(get_global_vtable(), $1, $3);
    set_template_typename("");
    set_function_returntype(NULL);
    clear_now_vtable();
  }
| NT_PROC_HEAD TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    $$ = (TProcDecl($1));
    vtable_add_cmd_list(get_global_vtable(), $1, $3);
    clear_now_vtable();
  }
| TM_FUNC NT_NAMED_HEAD
  {
    function_type_test_in_decl($2);
    $$ = TFuncProtoDecl($2);
  }
| NT_TEMPLATE_HEAD TM_FUNC NT_NAMED_HEAD
  {
    function_type_test_in_decl($3);
    set_function_template_typename($3,$1);
    $$ = TFuncProtoDecl($3);
    set_template_typename("");
  }
| TM_FUNC TM_VOID TM_IDENT TM_LEFT_PAREN NT_COMPLEX_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = TProcProtoDecl(TVarType(T_TYPENAME_VOID, TFuncType(TIntType($3), $5)));
  }

/* | NT_TEMPLATE_PROC_HEAD TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    
    vtable_add_cmd_list(get_global_vtable(), $1, $3);
    $$ = (TProcDecl($1));
    set_template_typename("");
    clear_now_vtable();
  } */
/* | NT_FOR_CMD
  {
    $$ = $1
  } */
;

NT_LOCAL_CMD_LIST:
  NT_LOCAL_CMD TM_SEMICOL NT_LOCAL_CMD_LIST
  {
    $$ = TCLCons($1, $3);
  }
| NT_LOCAL_CMD TM_SEMICOL
  {
    $$ = TCLCons($1, TCLNil());
  }
;

// LOCAL CMD 不能再使用函数定义
NT_LOCAL_CMD:
  TM_VAR NT_NAMED_HEAD
  {
    $$ = (TDecl($2));
    vtable_add(get_now_vtable(), $2);
  }
| NT_FOR_CMD
  {
    $$ = $1
  }
;

// FOR_CMD 应当拒绝掉分号规约 以及任何函数\过程定义
NT_FOR_CMD:
  NT_EXPR TM_ASGNOP NT_EXPR
  {
    $$ = (TAsgn($1,$3));
  }
| NT_IF_HEAD TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN TM_THEN TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE TM_ELSE TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    $$ = (TIf($3,$7,$11));
    clear_now_vtable();
  }
| NT_WHILE_HEAD TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN TM_DO TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    $$ = (TWhileDo($3,$7));
    clear_now_vtable();
  }
| NT_DO_HEAD TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE TM_WHILE TM_LEFT_PAREN NT_EXPR TM_RIGHT_PAREN
  {
    $$ = (TDoWhile($3,$7));
    clear_now_vtable();
  }
| NT_FOR_HEAD TM_LEFT_PAREN NT_FOR_CMD TM_SEMICOL NT_EXPR TM_SEMICOL NT_FOR_CMD TM_RIGHT_PAREN TM_LEFT_BRACE NT_LOCAL_CMD_LIST TM_RIGHT_BRACE
  {
    $$ = (TFor($3,$5,$7,$10));
    clear_now_vtable();
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
    $$ = (TReturn(NULL));
  }
| TM_RETURN NT_EXPR
  {
    $$ = (TReturn($2));
  }
| NT_EXPR TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = (TProc($1,TELNil()));
  }
| NT_EXPR TM_LEFT_PAREN NT_EXPR_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = (TProc($1,$3));
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
    $$ = (TFunc($1,TELNil()));
  }
| NT_EXPR TM_LEFT_PAREN NT_EXPR_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = (TFunc($1,$3));
  }
| NT_EXPR TM_LT NT_ANNON_HEAD TM_GT
  {
    $$ = (TInstance($1,$3));
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
	$$ = TFuncType($1,TVTLNil());
  }
| TM_LEFT_PAREN NT_NAMED_RIGHT_EXPR TM_RIGHT_PAREN
  {
	$$ = ($2);
  }
;

NT_COMPLEX_ARGUMENT_TYPE_LIST:
  NT_NAMED_HEAD TM_COMMA NT_COMPLEX_ARGUMENT_TYPE_LIST
  {
	  $$ = TVTLCons($1, $3); 
  }
| NT_NAMED_HEAD
  {
	  $$ = TVTLCons($1, TVTLNil()) ; 
  }  
| NT_ANNON_HEAD TM_COMMA NT_COMPLEX_ARGUMENT_TYPE_LIST
  {
	  $$ = TVTLCons($1, $3); 
  }
| NT_ANNON_HEAD
  {
	  $$ = TVTLCons($1, TVTLNil()) ; 
  }
;

NT_ANNON_RIGHT_EXPR:
  TM_MUL
  {
    $$= TPtrType(TIntType(""));
  }
| TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$= TFuncType(TIntType(""), TVTLNil());
  }
| TM_MUL NT_ANNON_RIGHT_EXPR
  {
    $$= TPtrType($2);
  }
| NT_ANNON_RIGHT_EXPR TM_LEFT_PAREN TM_RIGHT_PAREN
  {
    $$ = TFuncType($1 , TVTLNil());
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
	  $$ = TELCons($1, $3); 
  }
| NT_EXPR
  {
	  $$ = TELCons($1, TELNil()) ; 
  }
;

NT_TYPE_NAME:
  TM_INTTYPE
  {
    $$ = T_TYPENAME_INT;
  }
| TM_TEMPLATE_TYPENAME
  {
    $$ = T_TYPENAME_TEMPLATE;
  }
;

NT_FUNC_HEAD:
  TM_FUNC NT_NAMED_HEAD
  {
    function_type_test_in_decl($2);
    func_decl_test($2);

    $$ = $2;
    vtable_add(get_global_vtable(), $2);

    set_function_returntype(TFuncReturnType($2));

    init_new_now_vtable();
    vtable_add_list(get_now_vtable(),get_vde_vtl($2->vde));
  }
;

NT_TEMPLATE_HEAD:
  TM_TEMPLATE TM_LT TM_TYPENAME TM_IDENT TM_GT
  {
    set_template_typename($4);
    $$ = $4;
  }
;


NT_TEMPLATE_FUNC_HEAD:
  NT_TEMPLATE_HEAD NT_FUNC_HEAD
  {
    set_function_template_typename($2,$1);
    $$ = $2;
  }
;

NT_PROC_HEAD:
  TM_FUNC TM_VOID TM_IDENT TM_LEFT_PAREN NT_COMPLEX_ARGUMENT_TYPE_LIST TM_RIGHT_PAREN
  {
    $$ = TVarType(T_TYPENAME_VOID, TFuncType(TIntType($3), $5));
    proc_decl_test($$);
    vtable_add(get_global_vtable(), $$);
    init_new_now_vtable();
    vtable_add_list(get_now_vtable(),$5);
  }
;

NT_FOR_HEAD:
  TM_FOR
  {
    init_new_now_vtable();
  }
;
  
NT_WHILE_HEAD:
  TM_WHILE
  {
    init_new_now_vtable();
  }
;
  
NT_DO_HEAD:
  TM_DO
  {
    init_new_now_vtable();
  }
;
  
NT_IF_HEAD:
  TM_IF
  {
    init_new_now_vtable();
  }
;

NT_NAMED_HEAD:
  NT_TYPE_NAME NT_NAMED_RIGHT_EXPR
  {
    $$ = TVarType($1,$2);
  }
;

NT_ANNON_HEAD:
  NT_TYPE_NAME NT_ANNON_RIGHT_EXPR
  {
    $$ = TVarType($1,$2);
  }
| NT_TYPE_NAME 
  {
    $$ = TVarType($1,TIntType(""));
  }
;

%%

/* ----------------------------------
            Other Functions
   ---------------------------------- */

void yyerror(char* s)
{
    fprintf(stderr , "%s\n",s);
}
