#ifndef LANG_H_INCLUDED
#define LANG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

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
  T_TEMPLATEDECL,
  T_ASGN,
  T_SEQ,
  T_IF,
  T_DOWHILE,
  T_WHILEDO,
  T_FOR,
  T_LOCAL,
  T_CONTINUE,
  T_BREAK,
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
    struct { struct var_decl_expr * ret; struct decl_expr_type_list * args; } FUNC_TYPE;
  } d;
};

struct decl_expr_type_list {
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

struct typename_list {
  char * name;
  struct typename_list * next;
};

struct cmd {
  enum CmdType t;
  union {
    struct {struct var_decl_expr * right; } DECL;
    struct {struct typename_list * typenames; struct var_decl_expr * right; } TEMPLATEDECL;
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
    struct {struct expr * proc; struct expr_type_list * args; } PROC;
  } d;
};


struct decl_expr_type_list * TDETLNil();
struct decl_expr_type_list * TDETLCons(struct var_decl_expr * e, struct decl_expr_type_list * next);
struct expr_type_list * TETLNil();
struct expr_type_list * TETLCons(struct expr * e, struct expr_type_list * next);
struct typename_list * TTLNil();
struct typename_list * TTLCons(char * name, struct typename_list * next) ;
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
struct cmd * TDecl(struct var_decl_expr * right);
struct cmd * TTemplateDecl(struct typename_list * typenames, struct var_decl_expr * right);
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
struct cmd * TProc(struct expr * proc, struct expr_type_list * args);

void print_binop(enum BinOpType op);
void print_unop(enum UnOpType op);
void print_expr(struct expr * e);
void print_var_decl_expr(struct var_decl_expr * e);
void print_annon_var_decl_expr(struct var_decl_expr * e);
void print_cmd(struct cmd * c);

unsigned int build_nat(char * c, int len);
char * new_str(char * str, int len);

#endif // LANG_H_INCLUDED
