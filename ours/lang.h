#ifndef LANG_H_INCLUDED
#define LANG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

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

enum UnOpType {
  T_UMINUS,
  T_NOT
};

enum ExprType {
  T_CONST = 0,
  T_VAR,
  T_BINOP,
  T_UNOP,
  T_DEREF,
  T_ADDROF,
  T_FUNC
};

enum CmdType {
  T_DECL = 0,
  T_FUNCDECL,
  T_PROCDECL,
  T_ASGN,
  T_SEQ,
  T_IF,
  T_DOWHILE,
  T_WHILEDO,
  T_FOR,
  T_LOCAL,
  T_CONTINUE,
  T_BREAK,
  T_SKIP,
  T_RETURN,
  T_PROC
};

enum VarDeclType {
  T_INT_TYPE,
  T_PTR_TYPE,
  T_FUNC_TYPE
};

struct decl_expr_type_list;

struct var_decl_expr {
  enum VarDeclType t;
  union {
    struct { char * name; } INT_TYPE;
    struct { struct var_decl_expr * base; } PTR_TYPE;
    struct { char * name; struct var_decl_expr * ret; struct decl_expr_type_list * args; } FUNC_TYPE;
  } d;
};

struct decl_expr_type_list {
  char * typename;
  struct var_decl_expr * e;
  struct decl_expr_type_list * next;
};

struct expr_type_list;

struct expr {
  enum ExprType t;
  union {
    struct {unsigned int value; } CONST;
    struct {char * name; } VAR;
    struct {enum BinOpType op; struct expr * left; struct expr * right; } BINOP;
    struct {enum UnOpType op; struct expr * arg; } UNOP;
    struct {struct expr * arg; } DEREF;
    struct {struct expr * arg; } ADDROF;
    struct {struct expr * func; struct expr_type_list * args; } FUNC;
  } d;
};

struct expr_type_list {
  struct expr * e;
  struct expr_type_list * next;
};

struct cmd {
  enum CmdType t;
  union {
    struct {char * typename; struct var_decl_expr * right; } DECL;
    struct {char * typename; struct var_decl_expr * right; struct cmd * body; } FUNCDECL;
    struct {char * typename; struct var_decl_expr * right; struct cmd * body; } PROCDECL;
    struct {struct expr * left; struct expr * right; } ASGN;
    struct {struct cmd * left; struct cmd * right; } SEQ;
    struct {struct expr * cond; struct cmd * left; struct cmd * right; } IF;
    struct {struct expr * cond; struct cmd * body; } WHILEDO;
    struct {struct cmd * body; struct expr * cond;} DOWHILE;
    struct {struct cmd * init; struct expr * cond; struct cmd * nxt; struct cmd * body; } FOR;
    struct {char * var; struct cmd * body; } LOCAL;
    struct {void * none; } CONTINUE;
    struct {void * none; } BREAK;
    struct {void * none; } RETURN;
    struct {void * none; } SKIP;
    struct {struct expr * proc; struct expr_type_list * args; } PROC;
  } d;
};

struct var_type{
  char * typename;
  struct var_decl_expr * vde;
};

struct variable_table{
  dictionary * vtable;
  struct variable_table * father_vtable;
};

struct decl_expr_type_list * TDETLNil();
struct decl_expr_type_list * TDETLCons(char * typename, struct var_decl_expr * e, struct decl_expr_type_list * next);
struct expr_type_list * TETLNil();
struct expr_type_list * TETLCons(struct expr * e, struct expr_type_list * next);
struct var_decl_expr * TIntType(char * name);
struct var_decl_expr * TPtrType(struct var_decl_expr * base);
struct var_decl_expr * TFuncType(struct var_decl_expr * ret, struct decl_expr_type_list * args);
struct expr * TConst(unsigned int value);
struct expr * TVar(char * name);
struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right);
struct expr * TUnOp(enum UnOpType op, struct expr * arg);
struct expr * TDeref(struct expr * arg);
struct expr * TAddrOf(struct expr * arg);
struct expr * TFunc(struct expr * func, struct expr_type_list * args);
struct cmd * TDecl(char * typename, struct var_decl_expr * right);
struct cmd * TFuncDecl(char * typename, struct var_decl_expr * right, struct cmd * body);
struct cmd * TProcDecl(char * typename, struct var_decl_expr * right, struct cmd * body);
struct cmd * TAsgn(struct expr * left, struct expr * right);
struct cmd * TSeq(struct cmd * left, struct cmd * right);
struct cmd * TIf(struct expr * cond, struct cmd * left, struct cmd * right);
struct cmd * TWhileDo(struct expr * cond, struct cmd * body);
struct cmd * TDoWhile(struct cmd * body, struct expr * cond);
struct cmd * TFor(struct cmd * init, struct expr * cond, struct cmd * nxt, struct cmd * body);
struct cmd * TLocal(char * var, struct cmd * body);
struct cmd * TBreak();
struct cmd * TContinue();
struct cmd * TReturn();
struct cmd * TSkip();
struct cmd * TProc(struct expr * proc, struct expr_type_list * args);
struct var_type * TVarType(char * typename, struct var_decl_expr * vde);


void init_global_vtable();
void init_new_now_vtable();
void clear_now_vtable();
struct variable_table * get_global_vtable();
struct variable_table * get_now_vtable();
void vtable_add(struct variable_table * vtable, char * left_typename, struct var_decl_expr * e);
void vtable_del(struct variable_table * vtable, struct var_decl_expr * e);
struct var_type * vtable_find_vde(struct variable_table * vtable, struct var_decl_expr * e);
struct var_type * vtable_find_char(struct variable_table * vtable, char * var_name);
void set_template_typename(char * typename);
char * get_template_typename();
// int validate_typename_char(char * additional_typename, char * type);
// int validate_typename_vde(char * additional_typename, struct var_decl_expr * vde);
// int validate_typename_cmd(char * additional_typename, struct cmd * vde);

void print_binop(enum BinOpType op);
void print_unop(enum UnOpType op);
void print_expr(struct expr * e);
char * print_vde(struct var_decl_expr * e);
void print_typename_vde(char * varname, struct var_decl_expr * e);
void print_annon_var_decl_expr(struct var_decl_expr * e);
void print_cmd(struct cmd * c);

unsigned int build_nat(char * c, int len);
char * new_str(char * str, int len);

#endif // LANG_H_INCLUDED
