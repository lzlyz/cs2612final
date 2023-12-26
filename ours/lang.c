
/*-------------------------------------------------------------------------*/
/**
   @file    lang.c
   @brief   Implements of lexical analysis, grammar analysis, 
            grammar tree output, type check, polymorphic function expansion.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang.h"
#include "dictionary.h"

/*---------------------------------------------------------------------------
                        Grammar tree private functions
 ---------------------------------------------------------------------------*/

struct var_type * new_var_type_ptr() {
  struct var_type * res =
    (struct var_type *) malloc(sizeof(struct var_type));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct var_type_list * new_var_type_list_ptr() {
  struct var_type_list * res =
    (struct var_type_list *) malloc(sizeof(struct var_type_list));
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

/* Allocate a new pointer of variable_table. */
struct variable_table * new_vtable_ptr() {
  struct variable_table * res =
    (struct variable_table *) malloc(sizeof(struct variable_table));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/*---------------------------------------------------------------------------
                        Grammar tree function codes
 ---------------------------------------------------------------------------*/

/* Return a NULL pointer. */
struct var_type_list * TVTLNil() {
  return NULL;
}

/* Allocate a pointer of var_type_list with given parameters. */
struct var_type_list * TVTLCons(struct var_type * vt, struct var_type_list * next) {
  struct var_type_list * res = new_var_type_list_ptr();
  res -> vt = vt;
  res -> next = next;
  return res;
}

/* Return a NULL pointer. */
struct expr_type_list * TETLNil() {
  return NULL;
}

/* Allocate a pointer of var_type_list with given parameters. */
struct expr_type_list * TETLCons(struct expr * e, struct expr_type_list * next) {
  struct expr_type_list * res = new_expr_type_list_ptr();
  res -> e = e;
  res -> next = next;
  return res;
}

/* Allocate a pointer of var_decl_expr of INT_TYPE with given parameters. */
struct var_decl_expr * TIntType(char * name) {
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  res -> t = T_INT_TYPE;
  res -> d.INT_TYPE.name = name;
  return res;
}

/* Allocate a pointer of var_decl_expr of PTR_TYPE with given parameters. */
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
    res -> d.FUNC_TYPE.templatename = NULL;
    res -> d.FUNC_TYPE.body = NULL;
    free(base);
    break;
  }
  return res;
}

/* Allocate a pointer of var_decl_expr of FUNC_TYPE with given parameters. */
struct var_decl_expr * TFuncType(struct var_decl_expr * e, struct var_type_list * args) {
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
    res -> d.FUNC_TYPE.templatename = NULL;
    res -> d.FUNC_TYPE.body = NULL;
    free(e);
    break;
  }
  return res;
}

/* Allocate a pointer of expr of CONST with given parameters. */
struct expr * TConst(unsigned int value) {
  struct expr * res = new_expr_ptr();
  res -> t = T_CONST;
  res -> d.CONST.value = value;
  res -> vt = TVarType("int",TIntType(""));
  return res;
}

/* Allocate a pointer of expr of CONST with given parameters. */
struct expr * TVar(char * name) {
  struct expr * res = new_expr_ptr();
  res -> t = T_VAR;
  res -> d.VAR.name = name;
  res -> vt = vtable_find_char(get_now_vtable(),name);
  return res;
}

/* Allocate a pointer of expr of BINOP with given parameters. */
struct expr * TBinOp(enum BinOpType op, struct expr * left, struct expr * right) {
  struct expr * res = new_expr_ptr();
  res -> t = T_BINOP;
  res -> d.BINOP.op = op;
  res -> d.BINOP.left = left;
  res -> d.BINOP.right = right;
  if(!vt_cmp(left->vt,right->vt)){
    printf("[Error] Variable type unmatch in ");
    print_binop(op);
    printf("(");
    print_expr(left);
    printf(",");
    print_expr(right);
    printf(")");
    putchar('\n');
    exit(0);
  }
  res -> vt = left -> vt;
  return res;
}

/* Allocate a pointer of expr of UNOP with given parameters. */
struct expr * TUnOp(enum UnOpType op, struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_UNOP;
  res -> d.UNOP.op = op;
  res -> d.UNOP.arg = arg;
  res -> vt = arg -> vt;
  return res;
}

/* Allocate a pointer of expr of DEREF with given parameters. */
struct expr * TDeref(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_DEREF;
  res -> d.DEREF.arg = arg;
  if(arg -> vt -> vde -> t != T_PTR_TYPE){
    printf("[Error] Variable type is not Pointer when Deref(");
    print_expr(arg);
    printf(")");
    putchar('\n');
    exit(0);
  }
  res -> vt = TVarType(arg->vt->typename,arg->vt->vde->d.PTR_TYPE.base);
  return res;
}

/* Allocate a pointer of expr of ADDROF with given parameters. */
struct expr * TAddrOf(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_ADDROF;
  res -> d.ADDROF.arg = arg;
  res -> vt = TVarType(arg->vt->typename,TPtrType(arg -> vt->vde));
  return res;
}


/* Allocate a pointer of expr of INSTANCE with given parameters. */
struct expr * TInstance(struct expr * func, struct var_type * vt){
  if(func -> vt -> vde -> t != T_FUNC_TYPE){
    printf("[Error] Variable type is not Function when Instance(");
    print_expr(func);
    printf(",");
    print_vartype(vt);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(func -> vt -> vde->d.FUNC_TYPE.templatename== NULL){
    printf("[Error] Given function is not a template function when Induction(");
    print_expr(func);
    printf(",");
    print_vartype(vt);
    printf(")");
    putchar('\n');
    exit(0);
  }
  struct expr * res = new_expr_ptr();
  res -> t = T_INSTANCE;
  res -> d.INSTANCE.func = func;
  res -> d.INSTANCE.vt = vt;
  res -> vt = template_expand_vt(vt,func->vt,func -> vt -> vde->d.FUNC_TYPE.templatename);
  // print_vartype(func->vt);
  // print_vartype(res->vt);
  return res;
}

/* Allocate a pointer of expr of FUNC with given parameters. */
struct expr * TFunc(struct expr * func, struct expr_type_list * args) {
  struct expr * res = new_expr_ptr();
  res -> t = T_FUNC;
  res -> d.FUNC.func = func;
  res -> d.FUNC.args = args;
  if(func -> vt -> vde -> t != T_FUNC_TYPE || strcmp(func->vt->typename,"void")==0){
    printf("[Error] Variable type is not Function when Function(");
    print_expr(func);
    printf(",");
    print_expr_type_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(!etl_vtl_cmp(args,func->vt->vde->d.FUNC_TYPE.args)){
    printf("[Error] Arguments not match in Function(");
    print_expr(func);
    printf(",");
    print_expr_type_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  // printf("%s",func -> vt -> typename);
  // printf("yes");
  // print_vde(func -> vt -> vde);
  // printf("yes");
  // print_vde(func -> vt -> vde -> d.FUNC_TYPE.ret);
  // printf("yes");
  res -> vt = TVarType(func -> vt -> typename,func -> vt -> vde -> d.FUNC_TYPE.ret);
  return res;
}

/* Allocate a pointer of cmd of DECL with given parameters. */
struct cmd * TDecl(struct var_type * vt) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DECL;
  if(vt->vde->t==T_FUNC_TYPE){
    printf("[Error] in Variable or Pointer Declare, not declare a Pointer or Variable.");
    exit(0);
  }
  res -> d.DECL.vt = vt;
  return res;
}

/* Allocate a pointer of cmd of FUNCDECL with given parameters. */
struct cmd * TFuncDecl(struct var_type * vt){
  struct cmd * res = new_cmd_ptr();
  res -> t = T_FUNCDECL;
  res -> d.FUNCDECL.vt = vt;
  return res;
}

/* Allocate a pointer of cmd of PROCDECL with given parameters. */
struct cmd * TProcDecl(struct var_type * vt){
  struct cmd * res = new_cmd_ptr();
  res -> t = T_PROCDECL;
  res -> d.PROCDECL.vt = vt;
  return res;
}

/* Allocate a pointer of cmd of ASGN with given parameters. */
struct cmd * TAsgn(struct expr * left, struct expr * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_ASGN;
  res -> d.ASGN.left = left;
  res -> d.ASGN.right = right;
  if(!vt_cmp(left->vt,right->vt)){
    printf("[Error] Variable type unmatch in ");
    printf("Assignment(");
    print_expr(left);
    printf(",");
    print_expr(right);
    printf(")");
    putchar('\n');
    exit(0);
  }
  return res;
}

/* Allocate a pointer of cmd of SEQ with given parameters. */
struct cmd * TSeq(struct cmd * left, struct cmd * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_SEQ;
  res -> d.SEQ.left = left;
  res -> d.SEQ.right = right;
  return res;
}

/* Allocate a pointer of cmd of IF with given parameters. */
struct cmd * TIf(struct expr * cond, struct cmd * left, struct cmd * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_IF;
  res -> d.IF.cond = cond;
  res -> d.IF.left = left;
  res -> d.IF.right = right;
  return res;
}

/* Allocate a pointer of cmd of WHILEDO with given parameters. */
struct cmd * TWhileDo(struct expr * cond, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_WHILEDO;
  res -> d.WHILEDO.cond = cond;
  res -> d.WHILEDO.body = body;
  return res;
}

/* Allocate a pointer of cmd of DOWHILE with given parameters. */
struct cmd * TDoWhile(struct cmd * body, struct expr * cond) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DOWHILE;
  res -> d.DOWHILE.cond = cond;
  res -> d.DOWHILE.body = body;
  return res;
}

/* Allocate a pointer of cmd of FOR with given parameters. */
struct cmd * TFor(struct cmd * init, struct expr * cond, struct cmd * nxt, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_FOR;
  res -> d.FOR.init = init;
  res -> d.FOR.cond = cond;
  res -> d.FOR.nxt = nxt;
  res -> d.FOR.body = body;
  return res;
}

/* Allocate a pointer of cmd of LOCAL with given parameters. */
struct cmd * TLocal(char * var, struct cmd * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_LOCAL;
  res -> d.LOCAL.var = var;
  res -> d.LOCAL.body = body;
  return res;
}

/* Allocate a pointer of cmd of BREAK. */
struct cmd * TBreak() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_BREAK;
  return res;
}

/* Allocate a pointer of cmd of CONTINUE. */
struct cmd * TContinue() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_CONTINUE;
  return res;
}

/* Allocate a pointer of cmd of RETURN with given parameters. */
struct cmd * TReturn(struct expr * e) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_RETURN;
  res -> d.RETURN.e = e;
  if(!(get_function_returntype()==NULL&&e==NULL)&&!vt_cmp(e->vt,get_function_returntype())){
    printf("[Error] Variable type unmatch in ");
    printf("Return(");
    print_expr(e);
    printf(")");
    putchar('\n');
    exit(0);
  }
  return res;
}

/* Allocate a pointer of cmd of SKIP. */
struct cmd * TSkip() {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_SKIP;
  return res;
}

/* Allocate a pointer of cmd of PROC with given parameters. */
struct cmd * TProc(struct expr * func, struct expr_type_list * args) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_PROC;
  res -> d.PROC.proc = func;
  res -> d.PROC.args = args;
  if(func -> vt -> vde -> t != T_FUNC_TYPE || strcmp(func -> vt -> typename,"void")){
    printf("[Error] Variable type is not Function when Function(");
    print_expr(func);
    printf(",");
    print_expr_type_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(!etl_vtl_cmp(args,func->vt->vde->d.FUNC_TYPE.args)){
    printf("[Error] Arguments not match in Process(");
    print_expr(func);
    printf(",");
    print_expr_type_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  return res;
}

/* Return a var_type pointer with given typename and var_decl_expr. */
struct var_type * TVarType(char * typename, struct var_decl_expr * vde){
  struct var_type * res = new_var_type_ptr();
  res -> typename = typename;
  res -> vde = vde;
  return res;
}

/* Assume given vt is funtion_type. Allocate a pointer of var_type with the return type of given vt. */
struct var_type * TFuncReturnType(struct var_type * vt){
  if(vt->vde->t!=T_FUNC_TYPE){
    yyerror("[Error] in TFuncReturnType, given var_type is not a function type. Mostly this error is caused by you are declaring a function but given var_decl_expr is not a function.");
    exit(0);
  }
  return TVarType(vt -> typename, vt -> vde -> d.FUNC_TYPE.ret);
}

/* Allocate a new variable_table with given father_vtable. */
struct variable_table * TNewVtable(struct variable_table * father_vtable){
  struct variable_table * res = new_vtable_ptr();
  res -> dict = dictionary_new(30);
  res -> father_vtable= father_vtable;
  return res;
}


/*---------------------------------------------------------------------------
                          Type check private functions
 ---------------------------------------------------------------------------*/

/* TEMPLATE_TYPENAME is used to record the template typename when checking the declaration of polymorphic functions. */
char * TEMPLATE_TYPENAME="";

/* function_returntype is used to record the return type of the functino when checking cmd "return". */
struct var_type * function_returntype;

/* global_vtable is the global variable table. 
   now_vtable is the current local variable table. */
struct variable_table * global_vtable;
struct variable_table * now_vtable;

/*---------------------------------------------------------------------------
                            Type check function codes
 ---------------------------------------------------------------------------*/

/* Compare whether two var_decl_expr are the same. If same, return 1, else 0. */
int vde_cmp(struct var_decl_expr * e1,struct var_decl_expr * e2){
  if(e1->t!=e2->t) return 0;
  switch(e1->t){
  case T_INT_TYPE:
    return 1;
  case T_PTR_TYPE:
    return vde_cmp(e1->d.PTR_TYPE.base,e2->d.PTR_TYPE.base);
  case T_FUNC_TYPE:
    return vtl_cmp(e1->d.FUNC_TYPE.args,e2->d.FUNC_TYPE.args)&&vde_cmp(e1->d.FUNC_TYPE.ret,e2->d.FUNC_TYPE.ret);
  }
}

/* Compare whether two var_type are the same. If same, return 1, else 0. */
int vt_cmp(struct var_type * vt1, struct var_type * vt2){
  return strcmp(vt1->typename,vt2->typename)==0&&vde_cmp(vt1->vde,vt2->vde);
}

/* Compare whether two var_type_list are the same. If same, return 1, else 0. */
int vtl_cmp(struct var_type_list * vtl1, struct var_type_list * vtl2){
  if(vtl1==vtl2) return 1;
  if(vtl1==NULL||vtl2==NULL) return 0;
  return vt_cmp(vtl1->vt,vtl2->vt)&&vtl_cmp(vtl1->next,vtl2->next);
}

/* Compare whether two expr_type_list are the same. If same, return 1, else 0. */
int etl_vtl_cmp(struct expr_type_list * etl, struct var_type_list * vtl){
  if(etl==NULL&&vtl==NULL) return 1;
  if(etl==NULL||vtl==NULL) return 0;
  return vt_cmp(etl->e->vt,vtl->vt)&&etl_vtl_cmp(etl->next,vtl->next);
}

/* Extract the name of var_decl_expr. */
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

/* Return the first var_type_list of a var_decl_expr. 
   Mostly this is used for extract the type of arguments of a (pointer of) function for type checking. */
struct var_type_list * get_vde_vtl(struct var_decl_expr * e){
  switch (e -> t) {
  case T_INT_TYPE:
    return NULL;
  case T_PTR_TYPE:
    return get_vde_vtl(e -> d.PTR_TYPE.base);
  case T_FUNC_TYPE:
    return e -> d.FUNC_TYPE.args;
  }
}

/* Set TEMPLATE_TYPENAME to given typename. */
void set_template_typename(char * typename){
  TEMPLATE_TYPENAME=typename;
}

/* Get TEMPLATE_TYPENAME. */
char * get_template_typename(){
  return TEMPLATE_TYPENAME;
}


/* Set function_returntype to given typename. */
struct var_type * set_function_returntype(struct var_type * vt){
  function_returntype=vt;
}

/* Get function_returntype. */
struct var_type * get_function_returntype(){
  return function_returntype;
}

/* Initialize global_vtable and now_vtable. */
void init_global_vtable(){
  now_vtable = global_vtable = TNewVtable(NULL);
}

/* Allocate a new local variable table.
   The new variable table use now_vtable as father variable table then assign the new one to now_vtable. */
void init_new_now_vtable(){
  now_vtable = TNewVtable(now_vtable);
}

/* Free now_vtable and assign the father of now_vtable to now_vtable. */
void clear_now_vtable(){
  struct variable_table * temp_vtable = now_vtable->father_vtable;
  dictionary_del(now_vtable->dict);
  free(now_vtable);
  now_vtable = temp_vtable;
}

/* Get global_vtable. */
struct variable_table * get_global_vtable(){
  return global_vtable;
}

/* Get now_vtable. */
struct variable_table * get_now_vtable(){
  return now_vtable;
}

/* Add a item(pointer of var_type) to given vtable. */
void vtable_add(struct variable_table * vtable, struct var_type * vt){
  char * name=get_vde_name(vt->vde);
  if(name==NULL||strlen(name)==0) return;
  dictionary_set(vtable->dict, name, vt);
}

/* Add a item(pointer of var_type) to given vtable. */
void vtable_add_list(struct variable_table * vtable, struct var_type_list * vtl){
  if(vtl==NULL) return;
  vtable_add(vtable,vtl->vt);
  vtable_add_list(vtable,vtl->next);
}

/* Find the correct item (require function type) in given variable table (mostly global variable table) and modify its cmd body. 
   This is mainly used to update functions in global variable table. */
void vtable_add_cmd(struct variable_table * vtable, struct var_type * vt, struct cmd * c){
  struct var_type * res = vtable_find_vde(vtable, vt->vde);
  if(res==NULL){
    printf("[Error] not find the item to add cmd,vartype:");
    print_vartype(vt);
    exit(0);
  }
  res->vde->d.FUNC_TYPE.body=c;
}

/* Find the correct item (require function type) in given variable table (mostly global variable table) and modify its templatename. 
   This is mainly used to update polymorphic functions in global variable table. */
void vtable_add_template(struct variable_table * vtable, struct var_type * vt, char * templatename){
  struct var_type * res = vtable_find_vde(vtable, vt->vde);
  if(res==NULL){
    printf("[Error] not find the item to add cmd,vartype:");
    print_vartype(vt);
    exit(0);
  }
  res->vde->d.FUNC_TYPE.templatename=templatename;
}

/* Delete a item(pointer of var_type) of given vtable. */
void vtable_del(struct variable_table * vtable, struct var_decl_expr * e){
  dictionary_unset(vtable->dict, get_vde_name(e));
}

/* Find the item(pointer of var_type) of given vtable using given var_decl_expr. */
struct var_type * vtable_find_vde(struct variable_table * vtable, struct var_decl_expr * e){
  return vtable_find_char(vtable,get_vde_name(e));
}

/* Find the item(pointer of var_type) of given vtable using given name. */
struct var_type * vtable_find_char(struct variable_table * vtable, char * var_name){
  if(vtable==NULL) return NULL;
  struct var_type * res = dictionary_get(vtable->dict, var_name,NULL);
  if(res==NULL) return vtable_find_char(vtable->father_vtable,var_name);
  else return res;
}

/*---------------------------------------------------------------------------
                    Polymorphic expansion private functions
 ---------------------------------------------------------------------------*/

/* None */
 
/*---------------------------------------------------------------------------
                      Polymorphic expansion function codes
 ---------------------------------------------------------------------------*/

/* If ifexpand==true, expand var_decl_expr without command body. */
struct var_decl_expr * template_expand_vde(struct var_type * expand, struct var_decl_expr* vde, char * template_typename,int ifexpand){
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  switch(vde->t){
  case T_INT_TYPE:
    if(ifexpand) res = expand->vde;
    else res = vde;
    return res;
  case T_PTR_TYPE:
    res->t=T_PTR_TYPE;
    res->d.PTR_TYPE.base = template_expand_vde(expand, vde->d.PTR_TYPE.base,template_typename,ifexpand);
    return res;
  case T_FUNC_TYPE:
    res->t=T_FUNC_TYPE;
    res->d.FUNC_TYPE.args=template_expand_vtl(expand, vde->d.FUNC_TYPE.args, template_typename);
    res->d.FUNC_TYPE.templatename=NULL;
    res->d.FUNC_TYPE.ret=template_expand_vde(expand, vde->d.FUNC_TYPE.ret, template_typename, ifexpand);
    res->d.FUNC_TYPE.name=vde->d.FUNC_TYPE.name;
    res->d.FUNC_TYPE.body=vde->d.FUNC_TYPE.body; // TODO: fix body Typename expand
    return res;
  }
}

/* Expand var_type */
struct var_type * template_expand_vt(struct var_type * expand, struct var_type * vt, char * template_typename){
  struct var_type * res = new_var_type_ptr();
  int ifexpand = strcmp(vt->typename,template_typename)==0;
  if(ifexpand){
    res -> typename = expand->typename;
  }
  else{
    res -> typename = vt->typename;
  }
  res -> vde = template_expand_vde(expand,vt->vde,template_typename,ifexpand);
  return res;
}

/* Expand var_type_list. */
struct var_type_list * template_expand_vtl(struct var_type * expand, struct var_type_list * vtl, char * template_typename){
  if(vtl==NULL) return NULL;
  struct var_type_list * res = new_var_type_list_ptr();
  res -> vt = template_expand_vt(expand, vtl->vt, template_typename);
  res -> next = template_expand_vtl(expand,vtl->next,template_typename);
  return res;
}

/* Test the whether the polynomial function can be expanded as limited copies. */
int template_test(){
  struct var_type * main_vt=vtable_find_char(get_global_vtable(),"main");
  if(main_vt==NULL){
    printf("[Error][Template Test]No \"main\" Function!");
    return 0;
  }
  return 0;
}



/*---------------------------------------------------------------------------
                    Grammar tree output private functions
 ---------------------------------------------------------------------------*/

/* indent is used for record the spaces that need to be printed. */
int indent = 0;

/* print spaces depending on indent. */
void print_spaces() {
  int i;
  for (i = 0; i < indent; ++ i) {
    printf("  ");
  }
}

/* print spaces and print given string. */
void pprintf(char * s) {
  print_spaces();
  printf("%s",s);
}
 
/*---------------------------------------------------------------------------
                      Grammar tree output function codes
 ---------------------------------------------------------------------------*/

/* print given var_type_list as arguments of functions. */
void print_var_type_list_as_argument_types(struct var_type_list * args) {
  if (args == NULL) {
    return;
  }
  print_spaces();
  printf("Argument type:\n");
  indent ++;
  print_vartype(args -> vt);
  indent --;
  print_var_type_list_as_argument_types(args -> next);
}

/* print given expr_type_list as arguments of calling functions. */
void print_expr_type_list_as_argument_types(struct expr_type_list * args) {
  if (args == NULL) {
    return;
  }
  indent ++;
  print_spaces();
  printf("Argument:");
  print_expr(args -> e);
  putchar('\n');
  indent --;
  print_expr_type_list_as_argument_types(args -> next);
}

/* print given var_decl_expr. */
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
    if(e->d.FUNC_TYPE.templatename){
      print_spaces();
      printf("Template name: %s\n",e->d.FUNC_TYPE.templatename);
    }
    print_spaces();
    printf("Arguments:\n");
    indent ++;
    print_var_type_list_as_argument_types(e -> d.FUNC_TYPE.args);
    indent --;
    print_spaces();
    printf("Return type: ");
    print_vde(e->d.FUNC_TYPE.ret);
    if(e->d.FUNC_TYPE.body){
      print_spaces();
      printf("Function Body: \n");
      indent ++;
      print_cmd(e->d.FUNC_TYPE.body);
      indent --;
    }
    indent --;
    return e -> d.FUNC_TYPE.name;
  }
}

/* print given var_type. */
void print_vartype(struct var_type * vt){
  print_spaces();
  printf("Left type: %s\n", vt->typename);
  print_spaces();
  printf("Right type: ");
  char * varname = print_vde(vt->vde);
  if(strlen(varname)) {
    print_spaces();
    printf("Varname: %s\n",varname);
  }
}

/* print given binary operator. */
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

/* print given unary operator. */
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

/* print given expr. */
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
  case T_INSTANCE:
    printf("INSTANCE(");
    indent ++;
    print_expr(e -> d.INSTANCE.func);
    printf(",\n");
    print_vartype(e->d.INSTANCE.vt);
    print_spaces();
    printf(")");
    indent --;
    break;
  case T_FUNC:
    printf("FUNCTION(");
    print_expr(e -> d.FUNC.func);
    printf(",\n");
    indent ++;
    print_spaces();
    printf("Arguments:\n");
    print_expr_type_list_as_argument_types(e -> d.FUNC.args);
    print_spaces();
    printf(")");
    indent --;
    break;
  }
  // print_vartype(e->vt);
}

/* print given cmd. */
void print_cmd(struct cmd * c) {
  switch (c -> t) {
  case T_DECL:
    pprintf("Variable Declare:\n");
    indent ++;
    print_vartype(c -> d.DECL.vt);
    indent --;
    break;
  case T_FUNCDECL:
    pprintf("Function Declare:\n");
    indent ++;
    print_vartype(c->d.FUNCDECL.vt);
    indent --;
    break;
  case T_PROCDECL:
    pprintf("Process Declare:\n");
    indent ++;
    print_vartype(c->d.PROCDECL.vt);
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
    pprintf("Return");
    if(c->d.RETURN.e){
      printf(": ");
      print_expr(c->d.RETURN.e);
      putchar('\n');
    }
    else{
      printf(";");
    }
    break;
  }
}

/*---------------------------------------------------------------------------
                            Other function codes
 ---------------------------------------------------------------------------*/

/* build nature number. */
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

/* allocate a new string. */
char * new_str(char * str, int len) {
  char * res = (char *) malloc(sizeof(char) * (len + 1));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  strcpy(res, str);
  return res;
}

