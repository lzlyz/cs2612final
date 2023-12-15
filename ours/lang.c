#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.h"

struct decl_expr_type_list * new_decl_expr_type_list_ptr() {
  struct decl_expr_type_list * res =
    (struct decl_expr_type_list *) malloc(sizeof(struct decl_expr_type_list));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct expr_type_list * new_expr_type_list_ptr() {
  struct expr_type_list * res =
    (struct expr_type_list *) malloc(sizeof(struct expr_type_list));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct var_decl_expr * new_var_decl_expr_ptr() {
  struct var_decl_expr * res =
    (struct var_decl_expr *) malloc(sizeof(struct var_decl_expr));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct expr * new_expr_ptr() {
  struct expr * res = (struct expr *) malloc(sizeof(struct expr));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct cmd * new_cmd_ptr() {
  struct cmd * res = (struct cmd *) malloc(sizeof(struct cmd));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct decl_expr_type_list * TDETLNil() {
  return NULL;
}

struct decl_expr_type_list * TDETLCons(char * typename, struct var_decl_expr * e, struct decl_expr_type_list * next) {
  struct decl_expr_type_list * res = new_decl_expr_type_list_ptr();
  res -> typename = typename;
  res -> e = e;
  res -> next = next;
  return res;
}

struct expr_type_list * TETLNil() {
  return NULL;
}

struct expr_type_list * TETLCons(struct expr * e, struct expr_type_list * next) {
  struct expr_type_list * res = new_expr_type_list_ptr();
  res -> e = e;
  res -> next = next;
  return res;
}

struct var_decl_expr * TIntType(char * name) {
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  res -> t = T_INT_TYPE;
  res -> d.INT_TYPE.name = name;
  return res;
}

struct var_decl_expr * TPtrType(struct var_decl_expr * base) {
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  res -> t = T_PTR_TYPE;
  res -> d.PTR_TYPE.base = base;
  return res;
}

struct var_decl_expr * TFuncType(struct var_decl_expr * ret, struct decl_expr_type_list * args) {
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  res -> t = T_FUNC_TYPE;
  res -> d.FUNC_TYPE.ret = ret;
  res -> d.FUNC_TYPE.args = args;
  return res;
}

struct expr * TConst(unsigned int value) {
  struct expr * res = new_expr_ptr();
  res -> t = T_CONST;
  res -> d.CONST.value = value;
  return res;
}

struct expr * TVar(char * name) {
  struct expr * res = new_expr_ptr();
  res -> t = T_VAR;
  res -> d.VAR.name = name;
  return res;
}

struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right) {
  struct expr * res = new_expr_ptr();
  res -> t = T_BINOP;
  res -> d.BINOP.op = op;
  res -> d.BINOP.left = left;
  res -> d.BINOP.right = right;
  return res;
}

struct expr * TUnOp(enum UnOpType op, struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_UNOP;
  res -> d.UNOP.op = op;
  res -> d.UNOP.arg = arg;
  return res;
}

struct expr * TDeref(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_DEREF;
  res -> d.DEREF.arg = arg;
  return res;
}

struct expr * TAddrOf(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_ADDROF;
  res -> d.ADDROF.arg = arg;
  return res;
}

struct expr * TFunc(struct expr * func, struct expr_type_list * args) {
  struct expr * res = new_expr_ptr();
  res -> t = T_FUNC;
  res -> d.FUNC.func = func;
  res -> d.FUNC.args = args;
  return res;
}

struct cmd * TDecl(char * typename, struct var_decl_expr * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DECL;
  res -> d.DECL.typename = typename;
  res -> d.DECL.right = right;
  return res;
}

struct cmd * TFuncDecl(char * typename, struct var_decl_expr * right, struct cmd * body){
  struct cmd * res = new_cmd_ptr();
  res -> t = T_FUNCDECL;
  res -> d.FUNCDECL.typename = typename;
  res -> d.FUNCDECL.right = right;
  res -> d.FUNCDECL.body = body;
  return res;
}

struct cmd * TProcDecl(char * typename, struct var_decl_expr * right, struct cmd * body){
  struct cmd * res = new_cmd_ptr();
  res -> t = T_PROCDECL;
  res -> d.PROCDECL.typename = typename;
  res -> d.PROCDECL.right = right;
  res -> d.PROCDECL.body = body;
  return res;
}

struct cmd * TAsgn(struct expr * left, struct expr * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_ASGN;
  res -> d.ASGN.left = left;
  res -> d.ASGN.right = right;
  return res;
}

struct cmd * TSeq(struct cmd * left, struct cmd * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_SEQ;
  res -> d.SEQ.left = left;
  res -> d.SEQ.right = right;
  return res;
}

struct cmd * TIf(struct expr * cond, struct cmd * left, struct cmd * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_IF;
  res -> d.IF.cond = cond;
  res -> d.IF.left = left;
  res -> d.IF.right = right;
  return res;
}

struct cmd * TWhileDo(struct expr * cond, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_WHILEDO;
  res -> d.WHILEDO.cond = cond;
  res -> d.WHILEDO.body = body;
  return res;
}

struct cmd * TDoWhile(struct cmd * body, struct expr * cond) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DOWHILE;
  res -> d.DOWHILE.cond = cond;
  res -> d.DOWHILE.body = body;
  return res;
}

struct cmd * TFor(struct cmd * init, struct expr * cond, struct cmd * nxt, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_FOR;
  res -> d.FOR.init = init;
  res -> d.FOR.cond = cond;
  res -> d.FOR.nxt = nxt;
  res -> d.FOR.body = body;
  return res;
}

struct cmd * TLocal(char * var, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_LOCAL;
  res -> d.LOCAL.var = var;
  res -> d.LOCAL.body = body;
  return res;
}

struct cmd * TContinue() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_CONTINUE;
  return res;
}

struct cmd * TSkip() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_SKIP;
  return res;
}

struct cmd * TBreak() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_BREAK;
  return res;
}

struct cmd * TReturn() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_RETURN;
  return res;
}

struct cmd * TProc(struct expr * func, struct expr_type_list * args) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_PROC;
  res -> d.PROC.proc = func;
  res -> d.PROC.args = args;
  return res;
}

char * TEMPLATE_TYPENAME="";
void set_template_typename(char * typename){
  TEMPLATE_TYPENAME=typename;
}
char * get_template_typename(){
  return TEMPLATE_TYPENAME;
}

int validate_typename_char(char * additional_typename, char * type){
  if(!strcmp(additional_typename,type)||!strcmp("int",type)) return 1;
  else return 0;
}

int validate_typename_vdel(char * additional_typename, struct decl_expr_type_list * elist){
  if(elist->next==NULL) return 1;
  if(!validate_typename_vde(additional_typename,elist->e)) return 0;
  return validate_typename_char(additional_typename,elist->typename)&&validate_typename_vdel(additional_typename,elist->next);
}

int validate_typename_vde(char * additional_typename, struct var_decl_expr * e){
  switch (e -> t) {
  case T_INT_TYPE:
    return 1;
  case T_PTR_TYPE:
    return validate_typename_vde(additional_typename, e -> d.PTR_TYPE.base);
  case T_FUNC_TYPE:
    if(!validate_typename_vdel(additional_typename, e->d.FUNC_TYPE.args)) return 0;
    else return validate_typename_vde(additional_typename, e -> d.FUNC_TYPE.ret);
  };
}

int validate_typename_cmd(char * additional_typename, struct cmd * c){
  switch(c -> t) {
  case T_DECL:
    if(!validate_typename_char(additional_typename,c -> d.DECL.typename)) return 0;
    else return validate_typename_vde(additional_typename,c -> d.DECL.right);
    break;
  case T_SEQ:
    if(!validate_typename_cmd(additional_typename,c -> d.SEQ.left)) return 0;
    else return validate_typename_cmd(additional_typename,c -> d.SEQ.left);
  default:
    return 1;
  }
}


int indent = 0;

void print_spaces() {
  int i;
  for (i = 0; i < indent; ++ i) {
    printf("  ");
  }
}

void print_int(){
  print_spaces();
  printf("Left type: int\n");
  return;
}

enum PrintRetType {
  T_INT_TYPE_RETURN,
  T_FUNC_TYPE_RETURN
};

struct print_ret {
  enum PrintRetType t;
  union {
    char * name;
    struct var_decl_expr * e;
  } d;
};

struct print_ret * IntTypeReturn(char * name) {
  struct print_ret * res =
    (struct print_ret *) malloc (sizeof (struct print_ret));
  res -> t = T_INT_TYPE_RETURN;
  res -> d.name = name;
  return res;
}

struct print_ret * FuncTypeReturn(struct var_decl_expr * e) {
  struct print_ret * res =
    (struct print_ret *) malloc (sizeof (struct print_ret));
  res -> t = T_FUNC_TYPE_RETURN;
  res -> d.e = e;
  return res;
}

void print_decl_expr_type_list_as_argument_types(struct decl_expr_type_list * args) {
  if (args == NULL) {
    return;
  }
  print_spaces();
  printf("Argument type:\n");
  indent ++;
  print_int();
  print_annon_var_decl_expr(args -> e);
  indent --;
  print_decl_expr_type_list_as_argument_types(args -> next);
}

void print_expr_type_list_as_argument_types(struct expr_type_list * args) {
  if (args == NULL) {
    return;
  }
  print_spaces();
  indent ++;
  printf("Argument:\n");
  print_expr(args -> e);
  indent --;
  print_expr_type_list_as_argument_types(args -> next);
}

struct print_ret * print_var_decl_expr_rec(struct var_decl_expr * e) {
  struct print_ret * res;
  switch (e -> t) {
  case T_INT_TYPE:
    return IntTypeReturn(e -> d.INT_TYPE.name);
  case T_PTR_TYPE:
    res = print_var_decl_expr_rec(e -> d.PTR_TYPE.base);
    printf("pointer of ");
    return res;
  case T_FUNC_TYPE:
    return FuncTypeReturn(e);
  }
}

char * print_var_decl_expr_rec2(struct var_decl_expr * e) {
  struct print_ret * r = print_var_decl_expr_rec(e);
  char * res;
  switch (r -> t) {
  case T_INT_TYPE_RETURN:
    res = r -> d.name;
    printf("the LHS type\n");
    free(r);
    return res;
  case T_FUNC_TYPE_RETURN:
    printf("the following function type\n");
    indent ++;
    print_spaces();
    printf("Return type: ");
    res = print_var_decl_expr_rec2(r -> d.e -> d.FUNC_TYPE.ret);
    print_decl_expr_type_list_as_argument_types(r -> d.e -> d.FUNC_TYPE.args);
    indent --;
    free(r);
    return res;
  }
}

void print_annon_var_decl_expr(struct var_decl_expr * e) {
  print_spaces();
  printf("Right type: ");
  char * name = print_var_decl_expr_rec2(e);
}

void print_var_decl_expr(struct var_decl_expr * e) {
  print_spaces();
  printf("Right type: ");
  char * name = print_var_decl_expr_rec2(e);
  print_spaces();
  printf("Var name: %s\n", name);
}

void print_binop(enum BinOpType op) {
  switch (op) {
  case T_PLUS:
    printf("PLUS");
    break;
  case T_MINUS:
    printf("MINUS");
    break;
  case T_MUL:
    printf("MUL");
    break;
  case T_DIV:
    printf("DIV");
    break;
  case T_MOD:
    printf("MOD");
    break;
  case T_LT:
    printf("LT");
    break;
  case T_GT:
    printf("GT");
    break;
  case T_LE:
    printf("LE");
    break;
  case T_GE:
    printf("GE");
    break;
  case T_EQ:
    printf("EQ");
    break;
  case T_NE:
    printf("NE");
    break;
  case T_AND:
    printf("AND");
    break;
  case T_OR:
    printf("OR");
    break;
  }
}

void print_unop(enum UnOpType op) {
  switch (op) {
  case T_UMINUS:
    printf("UMINUS");
    break;
  case T_NOT:
    printf("NOT");
    break;
  }
}

void print_expr(struct expr * e) {
  switch (e -> t) {
  case T_CONST:
    printf("CONST(%d)", e -> d.CONST.value);
    break;
  case T_VAR:
    printf("VAR(%s)", e -> d.VAR.name);
    break;
  case T_BINOP:
    print_binop(e -> d.BINOP.op);
    printf("(");
    print_expr(e -> d.BINOP.left);
    printf(",");
    print_expr(e -> d.BINOP.right);
    printf(")");
    break;
  case T_UNOP:
    print_unop(e -> d.UNOP.op);
    printf("(");
    print_expr(e -> d.UNOP.arg);
    printf(")");
    break;
  case T_DEREF:
    printf("DEREF(");
    print_expr(e -> d.DEREF.arg);
    printf(")");
    break;
  case T_ADDROF:
    printf("ADDROF(");
    print_expr(e -> d.ADDROF.arg);
    printf(")");
    break;  
  case T_FUNC:
    printf("FUNC(");
    print_expr(e -> d.FUNC.func);
    printf(",");
    print_expr_type_list_as_argument_types(e -> d.FUNC.args);
    printf(")");
    break;
  }
}

void print_cmd(struct cmd * c) {
  switch (c -> t) {
  case T_DECL:
    printf("DECL(");
    print_int();
    print_var_decl_expr(c -> d.DECL.right);
    printf(")");
    break;
  case T_ASGN:
    printf("ASGN(");
    print_expr(c -> d.ASGN.left);
    printf(",");
    print_expr(c -> d.ASGN.right);
    printf(")");
    break;
  case T_SEQ:
    printf("SEQ(");
    print_cmd(c -> d.SEQ.left);
    printf(",");
    print_cmd(c -> d.SEQ.right);
    printf(")");
    break;
  case T_IF:
    printf("IF(");
    print_expr(c -> d.IF.cond);
    printf(",");
    print_cmd(c -> d.IF.left);
    printf(",");
    print_cmd(c -> d.IF.right);
    printf(")");
    break;
  case T_WHILEDO:
    printf("WHILEDO(");
    print_expr(c -> d.WHILEDO.cond);
    printf(",");
    print_cmd(c -> d.WHILEDO.body);
    printf(")");
    break;
  case T_DOWHILE:
    printf("DOWHILE(");
    print_cmd(c -> d.DOWHILE.body);
    printf(",");
    print_expr(c -> d.DOWHILE.cond);
    printf(")");
    break;
  case T_FOR:
    printf("FOR(");
    print_cmd(c -> d.FOR.init);
    printf(",");
    print_expr(c -> d.FOR.cond);
    printf(",");
    print_cmd(c -> d.FOR.nxt);
    printf(",");
    print_cmd(c -> d.FOR.body);
    printf(")");
    break;
  case T_LOCAL:
    printf("LOCAL(");
    printf("%s", c -> d.LOCAL.var);
    printf(",");
    print_cmd(c -> d.LOCAL.body);
    printf(")");
    break;
  case T_PROC:
    printf("PROC(");
    print_expr(c -> d.PROC.proc);
    printf(",");
    print_expr_type_list_as_argument_types(c -> d.PROC.args);
    printf(")");
    break;
  case T_BREAK:
    printf("BREAK");
    break;
  case T_CONTINUE:
    printf("CONTINUE");
    break;
  case T_SKIP:
    printf("SKIP");
    break;
  case T_RETURN:
    printf("RETURN");
    break;
  }
}

unsigned int build_nat(char * c, int len) {
  int s = 0, i = 0;
  for (i = 0; i < len; ++i) {
    if (s > 429496729) {
      printf("We cannot handle natural numbers greater than 4294967295.\n");
      exit(0);
    }
    if (s == 429496729 && c[i] > '5') {
      printf("We cannot handle natural numbers greater than 4294967295.\n");
      exit(0);
    }
    s = s * 10 + (c[i] - '0');
  }
  return s;
}

char * new_str(char * str, int len) {
  char * res = (char *) malloc(sizeof(char) * (len + 1));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  strcpy(res, str);
  return res;
}

