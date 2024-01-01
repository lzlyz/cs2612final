
/*-------------------------------------------------------------------------*/
/**
   @file    lang.h
   @brief   Implements of lexical analysis, grammar analysis, 
            grammar tree output, type check, polymorphic function expansion.

*/
/*--------------------------------------------------------------------------*/

#ifndef LANG_H_INCLUDED
#define LANG_H_INCLUDED

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

/*---------------------------------------------------------------------------
                              New Enumerations
 ---------------------------------------------------------------------------*/

/* The enumeration of binary operations. */
enum BinOpType {
  T_PLUS,
  T_MINUS,
  T_MUL,
  T_DIV,
  T_MOD,
  T_LT,
  T_GT,
  T_LE,
  T_GE,
  T_EQ,
  T_NE,
  T_AND,
  T_OR
};

/* The enumeration of unary operations. */
enum UnOpType {
  T_UMINUS,
  T_NOT
};

/* The enumeration of expressions. */
enum ExprType {
  T_CONST = 0,
  T_VAR,
  T_BINOP,
  T_UNOP,
  T_DEREF,
  T_ADDROF,
  T_INSTANCE,
  T_FUNC
};

/* The enumeration of binary commands. */
enum CmdType {
  T_DECL = 0,
  T_FUNCDECL,
  T_PROCDECL,
  T_ASGN,
  T_IF,
  T_DOWHILE,
  T_WHILEDO,
  T_FOR,
  T_CONTINUE,
  T_BREAK,
  T_SKIP,
  T_RETURN,
  T_PROC
};

/* The enumeration of the right variable declaration expression(var_decl_expr). */
enum VarDeclType {
  T_INT_TYPE,
  T_PTR_TYPE,
  T_FUNC_TYPE
};

/* The enumeration of the right variable declaration expression(var_decl_expr). */
enum TypenameType {
  T_TYPENAME_INT=0,
  T_TYPENAME_VOID,
  T_TYPENAME_TEMPLATE
};

/*---------------------------------------------------------------------------
                              Types Prototypes
 ---------------------------------------------------------------------------*/

struct var_type_list;
struct var_decl_expr;
struct var_type;
struct var_type_list;
struct expr;
struct expr_list;
struct cmd;
struct cmd_list;
struct variable_table;

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/**
  @brief variable declaration expression.

  This object describe a right type variable delcaration expression.
  INT_TYPE only contains the name of the variable.
  PTR_TYPE only contains what it points to.
  FUNC_TYPE contains the name of polymorphic template, the name of variable,
  the list of arguments, the type of return value and the body of commands.
 */
struct var_decl_expr {
  enum VarDeclType t;
  union {
    struct { char * name; } INT_TYPE;
    struct { struct var_decl_expr * base; } PTR_TYPE;
    struct { char * templatename; char * name; struct var_decl_expr * ret; struct var_type_list * args; struct cmd * body; } FUNC_TYPE;
  } d;
};

/**
  @brief    variable type. 

  This object describe a full type of a variable. 
  This object contains the left typename and 
  the right variable declaration expression(var_decl_expr).
 */
struct var_type{
  enum TypenameType left_type;
  struct var_decl_expr * vde;
};

/**
  @brief    list of variable type.

  This object is a chain of variable type(var_type).
 */
struct var_type_list {
  struct var_type * vt;
  struct var_type_list * next;
};

/**
  @brief    expression.

  This object is the expression.
  CONST contains the exact value.
  VAR contains the name of the variable.
  BINOP contains the binary operation, the left expression and the right expression.
  UNOP contains the unary operation, the only expression.
  DEREF contains the target expression to dereference.
  ADDROF contains the target expression to get address.
  INSTANCE contains the expression of polymorphic function and target variable type.
  FUNC contains the expression of function and arguments.
 */
struct expr {
  enum ExprType t;
  struct var_type * vt;
  union {
    struct {unsigned int value; } CONST;
    struct {char * name; } VAR;
    struct {enum BinOpType op; struct expr * left; struct expr * right; } BINOP;
    struct {enum UnOpType op; struct expr * arg; } UNOP;
    struct {struct expr * arg; } DEREF;
    struct {struct expr * arg; } ADDROF;
    struct {struct expr * func; struct var_type * vt; } INSTANCE;
    struct {struct expr * func; struct expr_list * args; } FUNC;
  } d;
};

/**
  @brief    list of expression.

  This object is a chain of expressions(expr).
 */
struct expr_list {
  struct expr * e;
  struct expr_list * next;
};

/**
  @brief    command.

  This object is the command.
  DECL contains the variable type(var_type) to declare.
  FUNCDECL contains the polymorphic templatename(or not) and the variable type to declare.
  PROCDECL contains the polymorphic templatename(or not) and the variable type to declare.
  ASGN contains the left expression to be assigned and the right expression to assign.
  WHILEDO contains the condition and the command body.
  DOWHILE contains the command body and the condition.
  FOR contains the initialization command, the condition, the step command, the command body.
  CONTINUE, BREAK, SKIP contains nothing.
  RETURN contains what it will return.
  PROC contains the expression of a process and the arguments.
 */
struct cmd {
  enum CmdType t;
  union {
    struct {struct var_type * vt; } DECL;
    struct {struct var_type * vt;} FUNCDECL;
    struct {struct var_type * vt;} PROCDECL;
    struct {struct expr * left; struct expr * right; } ASGN;
    struct {struct expr * cond; struct cmd_list * left; struct cmd_list * right; } IF;
    struct {struct expr * cond; struct cmd_list * body; } WHILEDO;
    struct {struct cmd_list * body; struct expr * cond;} DOWHILE;
    struct {struct cmd * init; struct expr * cond; struct cmd * nxt; struct cmd_list * body; } FOR;
    struct {void * none; } CONTINUE;
    struct {void * none; } BREAK;
    struct {struct expr * e; } RETURN;
    struct {void * none; } SKIP;
    struct {struct expr * proc; struct expr_list * args; } PROC;
  } d;
};

/**
  @brief    list of commands.

  This object is a chain of commands(cmd).
 */
struct cmd_list{
  struct cmd * c;
  struct cmd_lsit * next;
};

/**
  @brief    item of variable table.

  This is the target of variable table.
  visited is used in polymorphic test.
  var_type is used in type check.
 */
struct vtable_item{
  int visited;
  struct var_type * vt;
};

/**
  @brief    variable table.

  Variable table contains a dictionary and the father.
  Variable table is used for looking up the variable type with given name.
  Since there exists global variable and local variable, father_vtable is used to 
  record the father variable table with a larger scope. 
 */
struct variable_table{
  dictionary * dict;
  struct variable_table * father_vtable;
};

/*---------------------------------------------------------------------------
                      Grammar Tree function prototypes
 ---------------------------------------------------------------------------*/

/* Return a NULL pointer. */
struct var_type_list * TVTLNil();

/* Allocate a pointer of var_type_list with given parameters. */
struct var_type_list * TVTLCons(struct var_type * vt, struct var_type_list * next);

/* Return a NULL pointer. */
struct expr_list * TELNil();

/* Allocate a pointer of EXPR_list with given parameters. */
struct expr_list * TELCons(struct expr * e, struct expr_list * next);

/* Return a NULL pointer. */
struct cmd_list * TCLNil();

/* Allocate a pointer of cmd_list with given parameters. */
struct cmd_list * TCLCons(struct cmd * c, struct cmd_list * next);

/* Allocate a pointer of var_decl_expr of INT_TYPE with given parameters. */
struct var_decl_expr * TIntType(char * name);

/* Allocate a pointer of var_decl_expr of PTR_TYPE with given parameters. */
struct var_decl_expr * TPtrType(struct var_decl_expr * base);

/* Allocate a pointer of var_decl_expr of FUNC_TYPE with given parameters. */
struct var_decl_expr * TFuncType(struct var_decl_expr * ret, struct var_type_list * args);

/* Allocate a pointer of expr of CONST with given parameters. */
struct expr * TConst(unsigned int value);

/* Allocate a pointer of expr of CONST with given parameters. */
struct expr * TVar(char * name);

/* Allocate a pointer of expr of BINOP with given parameters. */
struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right);

/* Allocate a pointer of expr of UNOP with given parameters. */
struct expr * TUnOp(enum UnOpType op, struct expr * arg);

/* Allocate a pointer of expr of DEREF with given parameters. */
struct expr * TDeref(struct expr * arg);

/* Allocate a pointer of expr of ADDROF with given parameters. */
struct expr * TAddrOf(struct expr * arg);

/* Allocate a pointer of expr of INSTANCE with given parameters. */
struct expr * TInstance(struct expr * func, struct var_type * vt);

/* Allocate a pointer of expr of FUNC with given parameters. */
struct expr * TFunc(struct expr * func, struct expr_list * args);

/* Allocate a pointer of cmd of DECL with given parameters. */
struct cmd * TDecl(struct var_type * vt);

/* Allocate a pointer of cmd of FUNCDECL with given parameters. */
struct cmd * TFuncDecl(struct var_type * vt);

/* Allocate a pointer of cmd of PROCDECL with given parameters. */
struct cmd * TProcDecl(struct var_type * vt);

/* Allocate a pointer of cmd of ASGN with given parameters. */
struct cmd * TAsgn(struct expr * left, struct expr * right);

/* Allocate a pointer of cmd of IF with given parameters. */
struct cmd * TIf(struct expr * cond, struct cmd_list * left, struct cmd_list * right);

/* Allocate a pointer of cmd of WHILEDO with given parameters. */
struct cmd * TWhileDo(struct expr * cond, struct cmd_list * body);

/* Allocate a pointer of cmd of DOWHILE with given parameters. */
struct cmd * TDoWhile(struct cmd_list * body, struct expr * cond);

/* Allocate a pointer of cmd of FOR with given parameters. */
struct cmd * TFor(struct cmd * init, struct expr * cond, struct cmd * nxt, struct cmd_list * body);

/* Allocate a pointer of cmd of BREAK. */
struct cmd * TBreak();

/* Allocate a pointer of cmd of CONTINUE. */
struct cmd * TContinue();

/* Allocate a pointer of cmd of RETURN with given parameters. */
struct cmd * TReturn(struct expr * e);

/* Allocate a pointer of cmd of SKIP. */
struct cmd * TSkip();

/* Allocate a pointer of cmd of PROC with given parameters. */
struct cmd * TProc(struct expr * proc, struct expr_list * args);

/* Allocate a pointer of var_type with given parameters. */
struct var_type * TVarType(enum TypenameType left_type, struct var_decl_expr * vde);

/* Assume given vt is funtion_type. Allocate a pointer of var_type with the return type of given vt. */
struct var_type * TFuncReturnType(struct var_type * vt);

/* Allocate a new variable_table with given father_vtable. */
struct variable_table * TNewVtable(struct variable_table * father_vtable);

/*---------------------------------------------------------------------------
                        Type check function prototypes
 ---------------------------------------------------------------------------*/

/* Get the type of a vde except PTR. */
int pointer_of_what(struct var_decl_expr * vde);

/* Compare whether two var_decl_expr are the same. If same, return 1, else 0. */
int vde_cmp(struct var_decl_expr * e1,struct var_decl_expr * e2);

/* Compare whether two var_type are the same. If same, return 1, else 0. */
int vt_cmp(struct var_type * vt1,struct var_type * vt2);

/* Compare whether two var_type_list are the same. If same, return 1, else 0. */
int vtl_cmp(struct var_type_list * vtl1, struct var_type_list * vtl2);

/* Compare whether two expr_list are the same. If same, return 1, else 0. */
int el_vtl_cmp(struct expr_list * el, struct var_type_list * vtl);

/* Extract the name of var_decl_expr. */
char * get_vde_name(struct var_decl_expr * e);

/* Return the first var_type_list of a var_decl_expr. 
   Mostly this is used for extract the type of arguments of a (pointer of) function for type checking. */
struct var_type_list * get_vde_vtl(struct var_decl_expr * e);

/* Set TEMPLATE_TYPENAME to given typename. */
void set_template_typename(char * typename);

/* Get TEMPLATE_TYPENAME. */
char * get_template_typename();

/* Set function_returntype to given typename. */
struct var_type * set_function_returntype(struct var_type * vt);

/* Get function_returntype. */
struct var_type * get_function_returntype();

/* Initialize global_vtable and now_vtable. */
void init_global_vtable();

/* Allocate a new local variable table.
   The new variable table use now_vtable as father variable table then assign the new one to now_vtable. */
void init_new_now_vtable();

/* Free now_vtable and assign the father of now_vtable to now_vtable. */
void clear_now_vtable();

/* Get global_vtable. */
struct variable_table * get_global_vtable();

/* Get now_vtable. */
struct variable_table * get_now_vtable();

/* Add a item(pointer of var_type) to given vtable. */
void vtable_add(struct variable_table * vtable, struct var_type * vt);

/* Add a item(pointer of var_type) to given vtable. */
void vtable_add_list(struct variable_table * vtable, struct var_type_list * vtl);

/* Find the correct item (require function type) in given variable table (mostly global variable table) and modify its cmd body. 
   This is mainly used to update functions in global variable table. */
void vtable_add_cmd(struct variable_table * vtable, struct var_type * vt, struct cmd * c);

/* Find the correct item (require function type) in given variable table (mostly global variable table) and modify its templatename. 
   This is mainly used to update polymorphic functions in global variable table. */
void vtable_add_template(struct variable_table * vtable, struct var_type * vt, char * templatename);

/* Find the correct item (require function type) in given variable table (mostly global variable table) and modify its visited.  */
void vtable_set_visited(struct variable_table * vtable, struct var_type * vt, int visited);

/* Delete a item(pointer of var_type) of given vtable. */
void vtable_del(struct variable_table * vtable, struct var_decl_expr * e);

/* Find the item(pointer of var_type) of given vtable using given var_decl_expr. */
struct vtable_item * vtable_find_vde(struct variable_table * vtable, struct var_decl_expr * e);


/*---------------------------------------------------------------------------
                  Polymorphic expansion function prototypes
 ---------------------------------------------------------------------------*/

/* If ifexpand==true, expand var_decl_expr without command body. */
struct var_decl_expr * template_expand_vde(struct var_type * expand, struct var_decl_expr* vde, int ifexpand);

/* Expand var_type */
struct var_type * template_expand_vt(struct var_type * expand, struct var_type * vt);

/* Expand var_type_list. */
struct var_type_list * template_expand_vtl(struct var_type * expand, struct var_type_list * vtl);

/* Test the whether the polynomial function can be expanded as limited copies. */
int polymorphic_expansion_test();

/*---------------------------------------------------------------------------
                  Grammar tree output function prototypes
 ---------------------------------------------------------------------------*/


/* print given var_type_list as arguments of calling functions. */
void print_var_type_list_as_argument_types(struct var_type_list * args);

/* print given expr_list as arguments of functions. */
void print_expr_list_as_argument_types(struct expr_list * args);

/* print given var_decl_expr. */
char * print_vde(struct var_decl_expr * e);

/* print given var_type. */
void print_vartype(struct var_type * vt);

/* print given binary operator. */
void print_binop(enum BinOpType op);

/* print given unary operator. */
void print_unop(enum UnOpType op);

/* print given expr. */
void print_expr(struct expr * e);

/* print given cmd. */
void print_cmd(struct cmd * c);

/* print given cmd_list. */
void print_cmd_list(struct cmd_list * cl);


/*---------------------------------------------------------------------------
                        Other function prototypes
 ---------------------------------------------------------------------------*/

/* build nature number. */
unsigned int build_nat(char * c, int len);

/* allocate a new string. */
char * new_str(char * str, int len);

#endif // LANG_H_INCLUDED
