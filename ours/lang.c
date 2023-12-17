#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.h"
#include "dictionary.h"

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
  switch(base->t){
  case T_INT_TYPE:
    res -> t = T_PTR_TYPE;
    res -> d.PTR_TYPE.base = base;
    break;
  case T_PTR_TYPE:
    res -> t = T_PTR_TYPE;
    res -> d.PTR_TYPE.base = TPtrType(base->d.PTR_TYPE.base);
    free(base);
    break;
  case T_FUNC_TYPE:
    res -> t = T_FUNC_TYPE;
    res -> d.FUNC_TYPE.name = base->d.FUNC_TYPE.name;
    res -> d.FUNC_TYPE.args = base->d.FUNC_TYPE.args;
    res -> d.FUNC_TYPE.ret = TPtrType(base->d.FUNC_TYPE.ret);
    free(base);
    break;
  }
  return res;
}

struct var_decl_expr * TFuncType(struct var_decl_expr * e, struct decl_expr_type_list * args) {
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  switch(e->t){
  case T_INT_TYPE:
    res -> t = T_FUNC_TYPE;
    res -> d.FUNC_TYPE.name = e -> d.INT_TYPE.name;
    res -> d.FUNC_TYPE.args = args;
    res -> d.FUNC_TYPE.ret = TIntType("");
    free(e);
    break;
  case T_PTR_TYPE:
    res -> t = T_PTR_TYPE;
    res -> d.PTR_TYPE.base = TFuncType(e -> d.PTR_TYPE.base, args);
    free(e);
    break;
  case T_FUNC_TYPE:
    res -> t = T_FUNC_TYPE;
    res -> d.FUNC_TYPE.name = e -> d.FUNC_TYPE.name;
    res -> d.FUNC_TYPE.args = e -> d.FUNC_TYPE.args;
    res -> d.FUNC_TYPE.ret = TFuncType(e -> d.FUNC_TYPE.ret, args);
    free(e);
    break;
  }
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

// int validate_typename_char(char * additional_typename, char * type){
//   if(!strcmp(additional_typename,type)||!strcmp("int",type)) return 1;
//   else return 0;
// }

// int validate_typename_vdel(char * additional_typename, struct decl_expr_type_list * elist){
//   if(elist->next==NULL) return 1;
//   if(!validate_typename_vde(additional_typename,elist->e)) return 0;
//   return validate_typename_char(additional_typename,elist->typename)&&validate_typename_vdel(additional_typename,elist->next);
// }

// int validate_typename_vde(char * additional_typename, struct var_decl_expr * e){
//   switch (e -> t) {
//   case T_INT_TYPE:
//     return 1;
//   case T_PTR_TYPE:
//     return validate_typename_vde(additional_typename, e -> d.PTR_TYPE.base);
//   case T_FUNC_TYPE:
//     if(!validate_typename_vdel(additional_typename, e->d.FUNC_TYPE.args)) return 0;
//     else return validate_typename_vde(additional_typename, e -> d.FUNC_TYPE.ret);
//   };
// }

// int validate_typename_cmd(char * additional_typename, struct cmd * c){
//   switch(c -> t) {
//   case T_DECL:
//     if(!validate_typename_char(additional_typename,c -> d.DECL.typename)) return 0;
//     else return validate_typename_vde(additional_typename,c -> d.DECL.right);
//     break;
//   case T_SEQ:
//     if(!validate_typename_cmd(additional_typename,c -> d.SEQ.left)) return 0;
//     else return validate_typename_cmd(additional_typename,c -> d.SEQ.left);
//   default:
//     return 1;
//   }
// }

struct var_type * new_var_type_ptr() {
  struct var_type * res =
    (struct var_type *) malloc(sizeof(struct var_type));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct var_type * TVarType(char * typename, struct var_decl_expr * vde){
  struct var_type * res = new_var_type_ptr();
  res -> typename = typename;
  res -> vde = vde;
  return res;
}

struct variable_table * new_vtable_ptr() {
  struct variable_table * res =
    (struct variable_table *) malloc(sizeof(struct variable_table));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct variable_table * TNewVtable(struct variable_table * father_vtable){
  struct variable_table * res = new_vtable_ptr();
  res -> vtable = dictionary_new(30);
  res -> father_vtable= father_vtable;
  return res;
}


// char * get_vde_name(struct var_decl_expr * e){
//   switch (e -> t) {
//   case T_INT_TYPE:
//     return e -> d.INT_TYPE.name;
//   case T_PTR_TYPE:
//     return get_vde_name(e -> d.PTR_TYPE.base);
//   case T_FUNC_TYPE:
//     return get_vde_name(e -> d.FUNC_TYPE.ret);
//   }
// }

char * get_vde_name(struct var_decl_expr * e){
  switch (e -> t) {
  case T_INT_TYPE:
    return e -> d.INT_TYPE.name;
  case T_PTR_TYPE:
    return get_vde_name(e -> d.PTR_TYPE.base);
  case T_FUNC_TYPE:
    return e -> d.FUNC_TYPE.name;
  }
}

struct variable_table * global_vtable;
struct variable_table * now_vtable;

void init_global_vtable(){
  now_vtable = global_vtable = TNewVtable(NULL);
}

void init_new_now_vtable(){
  now_vtable = TNewVtable(now_vtable);
}

void clear_now_vtable(){
  struct variable_table * temp_vtable = now_vtable->father_vtable;
  dictionary_del(now_vtable->vtable);
  free(now_vtable);
  now_vtable = temp_vtable;
}

struct variable_table * get_global_vtable(){
  return global_vtable;
}

struct variable_table * get_now_vtable(){
  return now_vtable;
}

void vtable_add(struct variable_table * vtable, char * left_typename, struct var_decl_expr * e){
  dictionary_set(vtable->vtable, get_vde_name(e), TVarType(left_typename, e));
}

void vtable_del(struct variable_table * vtable, struct var_decl_expr * e){
  dictionary_unset(vtable->vtable, get_vde_name(e));
}

struct var_type * vtable_find_vde(struct variable_table * vtable, struct var_decl_expr * e){
  return vtable_find_char(vtable,get_vde_name(e));
}

struct var_type * vtable_find_char(struct variable_table * vtable, char * var_name){
  if(vtable==NULL) return NULL;
  struct var_type * res = dictionary_get(vtable->vtable, var_name,NULL);
  if(res==NULL) return vtable_find_char(vtable->father_vtable,var_name);
  else return res;
}


int indent = 0;

void print_spaces() {
  int i;
  for (i = 0; i < indent; ++ i) {
    printf("  ");
  }
}

void pprintf(char * s) {
  print_spaces();
  printf("%s",s);
}

void print_decl_expr_type_list_as_argument_types(struct decl_expr_type_list * args) {
  if (args == NULL) {
    return;
  }
  print_spaces();
  printf("Argument type:\n");
  indent ++;
  print_typename_vde(args->typename,args->e);
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

char * print_vde(struct var_decl_expr * e) {
  switch (e -> t) {
  case T_INT_TYPE:
    printf("the LHS type\n");
    return e->d.INT_TYPE.name;
  case T_PTR_TYPE:
    printf("Pointer to ");
    return print_vde(e->d.PTR_TYPE.base);
  case T_FUNC_TYPE:
    printf("Function of the following type\n");
    indent ++;
    print_spaces();
    printf("Arguments:\n");
    indent ++;
    print_decl_expr_type_list_as_argument_types(e -> d.FUNC_TYPE.args);
    indent --;
    print_spaces();
    printf("Return type: ");
    print_vde(e->d.FUNC_TYPE.ret);
    indent --;
    return e -> d.FUNC_TYPE.name;
  }
}

void print_typename_vde(char * typename,struct var_decl_expr * e) {
  print_spaces();
  printf("Left type: %s\n", typename);
  print_spaces();
  printf("Right type: ");
  char * varname = print_vde(e);
  if(strlen(varname)) {
    print_spaces();
    printf("Varname: %s\n",varname);
  }
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
    pprintf("Variable Declare:\n");
    indent ++;
    print_typename_vde(c -> d.DECL.typename, c -> d.DECL.right);
    indent --;
    break;
  case T_ASGN:
    pprintf("Assignment:\n");
    indent ++;
    pprintf("Left:");
    print_expr(c -> d.ASGN.left);
    putchar('\n');
    pprintf("Right:");
    print_expr(c -> d.ASGN.right);
    putchar('\n');
    indent --;
    break;
  case T_SEQ:
    print_cmd(c -> d.SEQ.left);
    print_cmd(c -> d.SEQ.right);
    break;
  case T_IF:
    pprintf("If:\n");
    indent ++;
    pprintf("Condition:");
    print_expr(c -> d.IF.cond);
    putchar('\n');
    pprintf("Then:\n");
    print_cmd(c -> d.IF.left);
    pprintf("Else:\n");
    print_cmd(c -> d.IF.right);
    indent --;
    break;
  case T_WHILEDO:
    pprintf("WhileDo:\n");
    indent ++;
    pprintf("Condition:");
    print_expr(c -> d.WHILEDO.cond);
    putchar('\n');
    pprintf("Body:");
    print_cmd(c -> d.WHILEDO.body);
    putchar('\n');
    indent --;
    break;
  case T_DOWHILE:
    pprintf("DoWhile:\n");
    indent ++;
    pprintf("Body:\n");
    print_cmd(c -> d.DOWHILE.body);
    pprintf("Condition:");
    print_expr(c -> d.DOWHILE.cond);
    putchar('\n');
    indent --;
    break;
  case T_FOR:
    pprintf("For:\n");
    indent ++;
    pprintf("Initilization:\n");
    print_cmd(c -> d.FOR.init);
    pprintf("Condition:");
    print_expr(c -> d.FOR.cond);
    putchar('\n');
    pprintf("NextStep:\n");
    print_cmd(c -> d.FOR.nxt);
    pprintf("Body:\n");
    print_cmd(c -> d.FOR.body);
    putchar('\n');
    indent --;
    break;
  case T_LOCAL:
    pprintf("Local:\n");
    indent ++;
    print_spaces();
    printf("Variable:%s\n",c -> d.LOCAL.var);
    pprintf("Body:\n");
    print_cmd(c -> d.LOCAL.body);
    indent --;
    break;
  case T_PROC:
    pprintf("Process:\n");
    indent ++;
    pprintf("Process Head:");
    print_expr(c -> d.PROC.proc);
    putchar('\n');
    pprintf("Process Args:\n");
    print_expr_type_list_as_argument_types(c -> d.PROC.args);
    putchar('\n');
    indent --;
    break;
  case T_BREAK:
    pprintf("Break;\n");
    break;
  case T_CONTINUE:
    pprintf("Continue;\n");
    break;
  case T_SKIP:
    pprintf("Skip;\n");
    break;
  case T_RETURN:
    pprintf("Return;\n");
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

