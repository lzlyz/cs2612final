
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

/* Allocate a new pointer of var_type. */
struct var_type * new_var_type_ptr() {
  struct var_type * res =
    (struct var_type *) malloc(sizeof(struct var_type));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of var_type_list. */
struct var_type_list * new_var_type_list_ptr() {
  struct var_type_list * res =
    (struct var_type_list *) malloc(sizeof(struct var_type_list));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of expr. */
struct expr * new_expr_ptr() {
  struct expr * res = (struct expr *) malloc(sizeof(struct expr));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of expr_list. */
struct expr_list * new_expr_list_ptr() {
  struct expr_list * res =
    (struct expr_list *) malloc(sizeof(struct expr_list));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of var_decl_expr. */
struct var_decl_expr * new_var_decl_expr_ptr() {
  struct var_decl_expr * res =
    (struct var_decl_expr *) malloc(sizeof(struct var_decl_expr));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of cmd. */
struct cmd * new_cmd_ptr() {
  struct cmd * res = (struct cmd *) malloc(sizeof(struct cmd));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of cmd_list. */
struct cmd_list * new_cmd_list_ptr() {
  struct cmd_list * res = (struct cmd_list *) malloc(sizeof(struct cmd_list));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of variable_table. */
struct vtable_item * new_vtable_item_ptr() {
  struct vtable_item * res =
    (struct vtable_item *) malloc(sizeof(struct vtable_item));
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
struct expr_list * TELNil() {
  return NULL;
}

/* Allocate a pointer of var_type_list with given parameters. */
struct expr_list * TELCons(struct expr * e, struct expr_list * next) {
  struct expr_list * res = new_expr_list_ptr();
  res -> e = e;
  res -> next = next;
  return res;
}

/* Return a NULL pointer. */
struct cmd_list * TCLNil() {
  return NULL;
}

/* Allocate a pointer of var_type_list with given parameters. */
struct cmd_list * TCLCons(struct cmd * c, struct cmd_list * next) {
  struct cmd_list * res = new_cmd_list_ptr();
  res -> c = c;
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
  res -> vt = vtable_find_char(get_now_vtable(),name)->vt;
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
    printf("[Info][Type check] Variable type unmatch in ");
    print_binop(op);
    printf("(");
    print_expr(left);
    printf(",");
    print_expr(right);
    printf(")");
    putchar('\n');
    exit(0);
  }  
  if(pointer_of_what(left->vt->vde)==T_FUNC_TYPE){
    printf("[Info][Type check] Variable type can not be (Pointer of)(*n) Function in");
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
  if(pointer_of_what(arg->vt->vde)==T_FUNC_TYPE){
    printf("[Info][Type check] Variable type can not be (Pointer of)(*n) Function in");
    print_unop(op);
    printf("(");
    print_expr(arg);
    printf(")");
    putchar('\n');
    exit(0);
  }
  return res;
}

/* Allocate a pointer of expr of DEREF with given parameters. */
struct expr * TDeref(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_DEREF;
  res -> d.DEREF.arg = arg;
  if(arg -> vt -> vde -> t != T_PTR_TYPE){
    printf("[Error][Type check] Variable type is not Pointer when Deref(");
    print_expr(arg);
    printf(")");
    putchar('\n');
    exit(0);
  }
  res -> vt = TVarType(arg->vt->left_type,arg->vt->vde->d.PTR_TYPE.base);
  return res;
}

/* Allocate a pointer of expr of ADDROF with given parameters. */
struct expr * TAddrOf(struct expr * arg) {
  struct expr * res = new_expr_ptr();
  res -> t = T_ADDROF;
  res -> d.ADDROF.arg = arg;
  res -> vt = TVarType(arg->vt->left_type,TPtrType(arg -> vt->vde));
  return res;
}


/* Allocate a pointer of expr of INSTANCE with given parameters. */
struct expr * TInstance(struct expr * func, struct var_type * vt){
  if(func -> vt -> vde -> t != T_FUNC_TYPE){
    printf("[Error][Type check] Variable type is not Function when Instance(");
    print_expr(func);
    printf(",");
    print_vartype(vt);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(func -> vt -> vde->d.FUNC_TYPE.templatename== NULL){
    printf("[Error][Type check] Given function is not a template function when Induction(");
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
  res -> vt = template_expand_vt(vt,func->vt);
  // print_vartype(func->vt);
  // print_vartype(res->vt);
  return res;
}

/* Allocate a pointer of expr of FUNC with given parameters. */
struct expr * TFunc(struct expr * func, struct expr_list * args) {
  struct expr * res = new_expr_ptr();
  res -> t = T_FUNC;
  res -> d.FUNC.func = func;
  res -> d.FUNC.args = args;
  if(func -> vt -> vde -> t != T_FUNC_TYPE || func->vt->left_type==T_TYPENAME_VOID){
    printf("[Error][Type check] Variable type is not Function when Function(");
    print_expr(func);
    printf(",");
    print_expr_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(func -> vt -> vde -> d.FUNC_TYPE.templatename != NULL){
    printf("[Error][Type check] You can not call a polymorphic function without instance in Function(");
    print_expr(func);
    printf(",");
    print_expr_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(!el_vtl_cmp(args,func->vt->vde->d.FUNC_TYPE.args)){
    printf("[Error][Type check] Arguments do not match in Function(");
    print_expr(func);
    printf(",");
    print_expr_list_as_argument_types(args);
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
  res -> vt = TFuncReturnType(func->vt);
  return res;
}

/* Allocate a pointer of cmd of DECL with given parameters. */
struct cmd * TDecl(struct var_type * vt) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DECL;
  if(vt->vde->t==T_FUNC_TYPE){
    printf("[Error][Type check] in Variable or Pointer Declaration, not declare a Pointer or Variable.");
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
    printf("[Error][Type check] Variable type unmatched in ");
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

/* Allocate a pointer of cmd of IF with given parameters. */
struct cmd * TIf(struct expr * cond, struct cmd_list * left, struct cmd_list * right) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_IF;
  res -> d.IF.cond = cond;
  res -> d.IF.left = left;
  res -> d.IF.right = right;
  return res;
}

/* Allocate a pointer of cmd of WHILEDO with given parameters. */
struct cmd * TWhileDo(struct expr * cond, struct cmd_list * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_WHILEDO;
  res -> d.WHILEDO.cond = cond;
  res -> d.WHILEDO.body = body;
  return res;
}

/* Allocate a pointer of cmd of DOWHILE with given parameters. */
struct cmd * TDoWhile(struct cmd_list * body, struct expr * cond) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_DOWHILE;
  res -> d.DOWHILE.cond = cond;
  res -> d.DOWHILE.body = body;
  return res;
}

/* Allocate a pointer of cmd of FOR with given parameters. */
struct cmd * TFor(struct cmd * init, struct expr * cond, struct cmd * nxt, struct cmd_list * body) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_FOR;
  res -> d.FOR.init = init;
  res -> d.FOR.cond = cond;
  res -> d.FOR.nxt = nxt;
  res -> d.FOR.body = body;
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
    printf("[Error][Type check] Variable type unmatched in ");
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
struct cmd * TProc(struct expr * func, struct expr_list * args) {
  struct cmd * res = new_cmd_ptr();
  res -> t = T_PROC;
  res -> d.PROC.proc = func;
  res -> d.PROC.args = args;
  if(func -> vt -> vde -> t != T_FUNC_TYPE || func -> vt -> left_type!=T_TYPENAME_VOID){
    printf("[Error][Type check] Variable type is not Function when Function(");
    print_expr(func);
    printf(",");
    print_expr_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  if(!el_vtl_cmp(args,func->vt->vde->d.FUNC_TYPE.args)){
    printf("[Error][Type check] Arguments not match in Process(");
    print_expr(func);
    printf(",");
    print_expr_list_as_argument_types(args);
    printf(")");
    putchar('\n');
    exit(0);
  }
  return res;
}

/* Return a var_type pointer with given typename and var_decl_expr. */
struct var_type * TVarType(enum TypenameType left_type, struct var_decl_expr * vde){
  struct var_type * res = new_var_type_ptr();
  res -> left_type = left_type;
  res -> vde = vde;
  return res;
}

/* Assume given vt is funtion_type. Allocate a pointer of var_type with the return type of given vt. */
struct var_type * TFuncReturnType(struct var_type * vt){
  if(vt->vde->t!=T_FUNC_TYPE){
    yyerror("[Error][Type check] in TFuncReturnType, given var_type is not a function type. Mostly this error is caused by you are declaring a function but given var_decl_expr is not a function.");
    exit(0);
  }
  return TVarType(vt -> left_type, vt -> vde -> d.FUNC_TYPE.ret);
}

/* Allocate a new variable_table with given father_vtable. */
struct vtable_item * TNewVtableItem(struct var_type * vt){
  struct vtable_item * res = new_vtable_item_ptr();
  res -> visited = 0;
  res -> vt = vt;
  return res;
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

/* Get the type of a vde except PTR. */
int pointer_of_what(struct var_decl_expr * vde){
  switch(vde->t){
    case T_PTR_TYPE:
      return pointer_of_what(vde->d.PTR_TYPE.base);
    default:
      return vde->t;
  }
}

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
  return vt1->left_type==vt2->left_type&&vde_cmp(vt1->vde,vt2->vde);
}

/* Compare whether two var_type_list are the same. If same, return 1, else 0. */
int vtl_cmp(struct var_type_list * vtl1, struct var_type_list * vtl2){
  if(vtl1==vtl2) return 1;
  if(vtl1==NULL||vtl2==NULL) return 0;
  return vt_cmp(vtl1->vt,vtl2->vt)&&vtl_cmp(vtl1->next,vtl2->next);
}

/* Compare whether two expr_list are the same. If same, return 1, else 0. */
int el_vtl_cmp(struct expr_list * el, struct var_type_list * vtl){
  if(el==NULL&&vtl==NULL) return 1;
  if(el==NULL||vtl==NULL) return 0;
  return vt_cmp(el->e->vt,vtl->vt)&&el_vtl_cmp(el->next,vtl->next);
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
  dictionary_set(vtable->dict, name, TNewVtableItem(vt));
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
  struct vtable_item * res = vtable_find_vde(vtable, vt->vde);
  if(res==NULL){
    printf("[Error][Type check] not find the item to add cmd, vartype:");
    print_vartype(vt);
    exit(0);
  }
  if(res->vt->vde->t!=T_FUNC_TYPE){
    printf("[Error][Type check] the item to add cmd is not the function type, vartype:");
    print_vartype(vt);
    exit(0);
  }
  res->vt->vde->d.FUNC_TYPE.body=c;
}

/* Find the correct item (require function type) in given variable table (mostly global variable table) and modify its templatename. 
   This is mainly used to update polymorphic functions in global variable table. */
void vtable_add_template(struct variable_table * vtable, struct var_type * vt, char * templatename){
  struct vtable_item * res = vtable_find_vde(vtable, vt->vde);
  if(res==NULL){
    printf("[Error][Type check] not find the item to add cmd, vartype:");
    print_vartype(vt);
    exit(0);
  }
  if(res->vt->vde->t!=T_FUNC_TYPE){
    printf("[Error][Type check] the item to add cmd is not the function type, vartype:");
    print_vartype(vt);
    exit(0);
  }
  res->vt->vde->d.FUNC_TYPE.templatename=templatename;
}

/* vtable set visited */
void vtable_set_visited(struct variable_table * vtable, struct var_type * vt, int visited){
  struct vtable_item * res = vtable_find_vde(vtable, vt->vde);
  res->visited=visited;
}

/* Delete a item(pointer of var_type) of given vtable. */
void vtable_del(struct variable_table * vtable, struct var_decl_expr * e){
  dictionary_unset(vtable->dict, get_vde_name(e));
}

/* Find the item(pointer of var_type) of given vtable using given var_decl_expr. */
struct vtable_item * vtable_find_vde(struct variable_table * vtable, struct var_decl_expr * e){
  return vtable_find_char(vtable,get_vde_name(e));
}

/* Find the item(pointer of var_type) of given vtable using given name. */
struct vtable_item * vtable_find_char(struct variable_table * vtable, char * var_name){
  if(vtable==NULL) return NULL;
  struct vtable_item * res = dictionary_get(vtable->dict, var_name,NULL);
  if(res==NULL) return vtable_find_char(vtable->father_vtable,var_name);
  else return res;
}

/*---------------------------------------------------------------------------
                    Polymorphic expansion private functions
 ---------------------------------------------------------------------------*/

// 两者同时进行！polumorphic

// 展开的本质是展开INSTANCE语句为EXPR，而非函数调用语句，于是说，我们只需要对INSTANCE语句进行展开，那么原理就是枚举EXPR即可！

// 但是main函数也会正常调用其他非多态函数，这时候该怎么办呢？

// 也就是说，对于一个FUNC语句，我们先对EXPR进行递归，找到需要展开的INSTANCE，然后展开INSTANCE，然后再执行函数调用，此时进入展开好的函数开始查找

// 那么小伙伴们也会问了，之前实现的展开函数的代码并没有展开command body，这是肿么会是呢？

// 这个小编也不知道呢？

// 我们如下实现展开过程

// 首先枚举EXPR,遇到INSTANCE开始展开，从对应函数名字。遇到无限递归的时候，在第二次访问函数结束后再终止递归即可。

//注：多态函数无法定义函数指针，也就是说，expr<var_type>出现的条件一定要求expr是一个VAR
// 我们可以利用这一点，

//我们展开的时候需要建立从<string, var_type>到<instanced polymorphic function>，这个映射难以建立，我打算直接开个数组枚举算了，我真的曹乐，但是也很麻烦。
//dictionary库只支持从char*->void*的映射，内部使用strcmp实现的，我真是曹乐，要是CPP就可以用map了。

dictionary * polymorphic_expansion_dict; // 这个字典从 string 映射到一个 var_type_list

// FUNCTIONS OF POLYMORPHIC EXPANSION

struct instance_function{
  struct var_type * instance_vt;
  struct var_type * expanded_function;
};

struct instance_function_list{
  struct instance_function * insf;
  struct instance_function_list * next;
};

/* Allocate a new pointer of instance_function. */
struct instance_function * new_instance_function_ptr() {
  struct instance_function * res = (struct instance_function *) malloc(sizeof(struct instance_function));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

/* Allocate a new pointer of instance_function_list. */
struct instance_function_list * new_instance_function_list_ptr() {
  struct instance_function_list * res =
    (struct instance_function_list *) malloc(sizeof(struct instance_function_list));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}

struct instance_function * TInsFun(struct var_type * instance_vt, struct var_type * expanded_function){
  struct instance_function * res = new_instance_function_ptr();
  res -> instance_vt = instance_vt;
  res -> expanded_function = expanded_function;
  return res;
}

struct instance_function_list * TInsFunList(struct instance_function * insf, struct instance_function_list * next){
  struct instance_function_list * res = new_instance_function_list_ptr();
  res -> insf = insf;
  res -> next = next;
  return res;
} 


void ped_add(char * polymorphic_name, struct var_type * instance_vt, struct var_type * expanded_function){
  dictionary_set(polymorphic_expansion_dict, polymorphic_name, 
    TInsFunList(TInsFun(instance_vt,expanded_function),dictionary_get(polymorphic_expansion_dict,polymorphic_name,NULL)));
}

struct var_type * ped_find(char * polymorphic_name, struct var_type * instance_vt){
  if(polymorphic_name==NULL) return NULL;
  struct instance_function_list * ifl;
  for(ifl=dictionary_get(polymorphic_expansion_dict, polymorphic_name, NULL);
      ifl!=NULL;ifl=ifl->next){
    if(vt_cmp(instance_vt,ifl->insf->instance_vt)){
      return ifl->insf->expanded_function;
    }
  }
  return NULL;
}

/* Add expaned functions to the declaration. 
   I have to notice that the declarations of polynomial functions have not been deleted. 
   To delete them is a little complex. I think I'd rather to choose not to output them. 
   (2 ways to delete the polymorphic functions: 1. add previous to cmd_list, 
    2. use cl->next instead of cl and you need to modify root.) */
void ped_unfold_function_declare(const struct cmd_list * root){
  struct cmd_list * cl;
  for(cl=root;cl!=NULL;cl=cl->next){
    if(cl->c->t==T_FUNCDECL&&cl->c->d.FUNCDECL.vt->vde->d.FUNC_TYPE.templatename!=NULL){
      struct instance_function_list * ifl;
      for(ifl=dictionary_get(polymorphic_expansion_dict, cl->c->d.FUNCDECL.vt->vde->d.FUNC_TYPE.name, NULL);
          ifl!=NULL;ifl=ifl->next){
        cl->next=TCLCons(TFuncDecl(ifl->insf->expanded_function),cl->next);
      }
    }
  }
}


// function_stack 被用于储存当前已经调用了哪些函数，对于多态函数，只需要记录多态函数本身即可，但是这里存在一个难点
// 由于我们前面的关系 INSTANCE 在 函数调用之前，因此，INSTANCE会把多态函数转换为实例函数，这就产生了一个难点。
// 解决方法是，在实例化的时候，我们就已经需要进入多态函数拷贝副本进行实例化了，于是可以这样跳过

// 对于如下的情况
/*
template <typename T> func T f(T a){
  return &T<int *>(& a);
}

*/
// 处理方法是：在函数展开的过程中



// 判断条件可以简化，发生的情况应当仅仅限于一个多态函数实例化另一个多态函数的时候携带了多态类型名，所以判断无限副本的情况相当清晰了
// 目前只需要应对无穷递归的情况即可！我们还是把这两步分开吧！
// 首先进行展开检查，展开检查对每个函数进行递归，在一个多态函数内，应当记录当前的多态函数，然后考虑实例化，

struct function_stack{
  int stack_len;
  struct var_type_list * stack_of_type;
  struct var_type_list * stack_of_function;
};

/* Allocate a new pointer of function_stack. */
struct function_stack * new_function_stack_ptr() {
  struct function_stack * res =
    (struct function_stack *) malloc(sizeof(struct function_stack));
  if (res == NULL) {
    printf("Failure in malloc.\n");
    exit(0);
  }
  return res;
}


/* . */
struct visited_array * TFuncStack(){
  struct function_stack * res = new_function_stack_ptr();
  res -> stack_len = 0;
  res -> stack_of_function = NULL;
  res -> stack_of_type = NULL;
  return res;
}

void func_stack_push(struct function_stack * fs, const struct var_type * function, const struct var_type * type){
  fs->stack_of_function = TVTLCons(function,fs->stack_of_function);
  fs->stack_of_type = TVTLCons(type,fs->stack_of_type);
  fs->stack_len++;
}

int func_stack_pop(struct function_stack * fs){
  if(fs->stack_len==0) return 0;
  struct var_type_list * fl = fs->stack_of_function;
  struct var_type_list * tl = fs->stack_of_type;
  fs->stack_of_function = fs->stack_of_function->next;
  fs->stack_of_type = fs->stack_of_type->next;
  free(fl);
  free(tl);
  return 1;
}

void func_stack_delete(struct function_stack * fs){
  while(func_stack_pop(fs));
  free(fs);
}

int PFE_stack_exist(struct function_stack * fs, struct var_type * function, struct var_type * type){
  struct var_type_list * fl = fs->stack_of_function;
  struct var_type_list * tl = fs->stack_of_type;
  int len = fs->stack_len;
  while(len--) if(vt_cmp(function,fl->vt)&&vt_cmp(type,tl->vt)) return 1;
  return 0;
}

int vt_exists_template_typename(const struct var_type * vt);

int vtl_exists_template_typename(const struct var_type_list * vtl){
  struct var_type_list * vtl0 = vtl;
  for(vtl0=vtl;vtl0!=NULL;vtl0=vtl0->next){
    if(vt_exists_template_typename(vtl0->vt)) return 1;
  }
  return 0;
}

int vde_exists_template_typename(const struct var_decl_expr * vde){
  switch(vde->t){
    case T_INT_TYPE:
      return 0;
    case T_PTR_TYPE:
      return vde_exists_template_typename(vde->d.PTR_TYPE.base);
    case T_FUNC_TYPE:
      // Ignore body, templatename and name. They are unnecessary in NT_TYPE_NAME ANNON_EXPR.
      return vtl_exists_template_typename(vde->d.FUNC_TYPE.args)
            ||vde_exists_template_typename(vde->d.FUNC_TYPE.ret);
  }
}

int vt_exists_template_typename(const struct var_type * vt){
  return vt->left_type==T_TYPENAME_TEMPLATE||vde_exists_template_typename(vt->vde);
}

int vt_is_original_template_typename(const struct var_type * vt){
  return vt->left_type==T_TYPENAME_TEMPLATE&&vt->vde->t==T_INT_TYPE;
}

void PT_next_call(struct function_stack * fs, struct var_type * polymorphic_function, struct var_type * instance_type){
  if
}

void PT_expr(struct function_stack * fs, struct expr * e){
  switch(e->t){  
    case T_BINOP:
      PT_expr(fs, e->d.BINOP.left);
      PT_expr(fs, e->d.BINOP.right);
    case T_UNOP:
      PT_expr(fs, e->d.UNOP.arg);
    case T_DEREF:
      PT_expr(fs, e->d.DEREF.arg);
    case T_ADDROF:
      PT_expr(fs, e->d.ADDROF.arg);
    case T_INSTANCE:
      PFE_polymorphic_test(e->d.INSTANCE.func);
      PT_next_call(fs, e->d.INSTANCE.func, e->d.INSTANCE.vt);
    case T_FUNC:
      PT_expr(fs, e->d.FUNC.func);
      PT_expr_list(fs, e->d.FUNC.args);
  }
}

void PT_expr_list(struct function_stack * fs, struct expr_list * el){
  if(el==NULL) return;
  PT_expr(fs, el->e);
  PT_expr_list(fs, el->next);
}

void PT_cmd(struct function_stack * fs, struct cmd * c){
  switch(c->t){
    case T_ASGN:
      PT_expr(fs, c->d.ASGN.left);
      PT_expr(fs, c->d.ASGN.left);
      break;
    case T_IF:
      PT_expr(fs, c->d.IF.cond);
      PT_cmd_list(fs, c->d.IF.left);
      PT_cmd_list(fs, c->d.IF.right);
      break;
    case T_DOWHILE:
      PT_cmd_list(fs, c->d.DOWHILE.body);
      PT_expr(fs, c->d.DOWHILE.cond);
      break;
    case T_WHILEDO:
      PT_expr(fs, c->d.WHILEDO.cond);
      PT_cmd_list(fs, c->d.WHILEDO.body);
      break;
    case T_FOR:
      PT_cmd(fs, c->d.FOR.init);
      PT_expr(fs, c->d.FOR.cond);
      PT_cmd_list(fs, c->d.FOR.body);
      PT_cmd(fs, c->d.FOR.nxt);
      break;
    case T_RETURN:
      PT_expr(fs, c->d.RETURN.e);
      break;
    case T_PROC:
      PT_expr_list(fs, c->d.PROC.args);
      break;
  }
}

void PT_cmd_list(struct function_stack * fs, struct cmd_list * cl){
  if(cl==NULL) return;
  PT_cmd(fs,cl->c);
  PT_cmd_list(fs,cl->next);
}

void PFE_polymorphic_test(struct var_type * polymorphic_function){
  struct vtable_item * instanced_function = vtable_find_vde(get_global_vtable(),polymorphic_function->vde);
  if(instanced_function!=NULL&&instanced_function->visited==1){ 
    return;
  }
  struct function_stack * fs = TFUNCStack();
  func_stack_push(fs,polymorphic_function,TIntType(""));
  PT_cmd_list(fs,polymorphic_function->vde->d.FUNC_TYPE.body);
}

struct var_type * PFE_polymorphic_expand(){

}

/* change given instance expr. */
void PFE_expr_expand(struct expr * e){
  struct var_type * instance_function = ped_find(e->d.INSTANCE.func->vt->vde->d.FUNC_TYPE.name,e->d.INSTANCE.vt);
  if(instance_function==NULL){
    PFE_polymorphic_test(e->d.INSTANCE.func);
    instance_function = PFE_polymorphic_expand(e->d.INSTANCE.func, e->d.INSTANCE.vt);
    ped_add(e->d.INSTANCE.func->vt->vde->d.FUNC_TYPE.name,e->d.INSTANCE.func,instance_function);
  }
  e->t = T_VAR;
  e->d.VAR.name = instance_function->vde->d.FUNC_TYPE.name;
  e->vt = instance_function;
}

void PFE_expr_list(struct expr_list * el);

void PFE_visit_function(struct var_type * func);

/* return 1 if instance exists. */
int PFE_expr(const struct expr * e){
  switch(e->t){  
    case T_BINOP:
      PFE_expr(e->d.BINOP.left);
      PFE_expr(e->d.BINOP.right);
      return 0;
    case T_UNOP:
      PFE_expr(e->d.UNOP.arg);
      return 0;
    case T_DEREF:
      return PFE_expr(e->d.DEREF.arg);
    case T_ADDROF:
      return PFE_expr(e->d.ADDROF.arg);
    case T_INSTANCE:
      PFE_expr_expand(e);
      return 1;
    case T_FUNC:
      if(!PFE_expr(e->d.FUNC.func)&&!vtable_find_vde(get_global_vtable(),e->vt->vde)->visited) 
        PFE_visit_function(e->vt);
      PFE_expr_list(e->d.FUNC.args);
      return 0;
  }
  return 0;
}
// 多态函数实例化的时候就会创建模板，因此对于多态函数有两种处理需求：1.实际参与调用了多态函数，2，仅仅对多态函数进行了实例化。
// 由于在type check的过程中，我们已经给expr记录了其类型，那么我们只需要考虑T_INSTANCE和T_FUNC了
// 对于普通函数，肯定只能通过T_FUNC继续进行检查；那么对于多态函数，我们只需要让T_FUNC不再往下递归expr即可，这样T_FUNC和T_INSTANCE的冲突就解决了。

void PFE_expr_list(struct expr_list * el){
  if(el==NULL) return;
  PFE_expr(el->e);
  PFE_expr_list(el->next);
}

void PFE_cmd(struct cmd * c){
  switch(c->t){
    case T_ASGN:
      PFE_expr(c->d.ASGN.left);
      PFE_expr(c->d.ASGN.left);
      break;
    case T_IF:
      PFE_expr(c->d.IF.cond);
      PFE_cmd_list(c->d.IF.left);
      PFE_cmd_list(c->d.IF.right);
      break;
    case T_DOWHILE:
      PFE_cmd_list(c->d.DOWHILE.body);
      PFE_expr(c->d.DOWHILE.cond);
      break;
    case T_WHILEDO:
      PFE_expr(c->d.WHILEDO.cond);
      PFE_cmd_list(c->d.WHILEDO.body);
      break;
    case T_FOR:
      PFE_cmd(c->d.FOR.init);
      PFE_expr(c->d.FOR.cond);
      PFE_cmd_list(c->d.FOR.body);
      PFE_cmd(c->d.FOR.nxt);
      break;
    case T_RETURN:
      PFE_expr(c->d.RETURN.e);
      break;
    case T_PROC:
      PFE_next_call(c->d.PROC.proc);
      PFE_expr_list(c->d.PROC.args);
      break;
  }
}

void PFE_cmd_list(struct cmd_list * cl){
  if(cl==NULL) return;
  PFE_cmd(cl->c);
  PFE_cmd_list(cl->next);
}

void PFE_visit_function(struct var_type * func){
  vtable_set_visited(get_global_vtable(),func,1);
  PFE_cmd_list(func->vde->d.FUNC_TYPE.body);
}
 
/*--------------------------------------------------------------------------*\
                      Polymorphic expansion function codes
\*--------------------------------------------------------------------------*/

/* If ifexpand==true, expand var_decl_expr without command body. This is mainly used in type check. */
struct var_decl_expr * template_expand_vde(struct var_type * expand, struct var_decl_expr* vde,int ifexpand){
  struct var_decl_expr * res = new_var_decl_expr_ptr();
  switch(vde->t){
  case T_INT_TYPE:
    if(ifexpand) res = expand->vde;
    else res = vde;
    return res;
  case T_PTR_TYPE:
    res->t=T_PTR_TYPE;
    res->d.PTR_TYPE.base = template_expand_vde(expand, vde->d.PTR_TYPE.base,ifexpand);
    return res;
  case T_FUNC_TYPE:
    res->t=T_FUNC_TYPE;
    res->d.FUNC_TYPE.args=template_expand_vtl(expand, vde->d.FUNC_TYPE.args);
    res->d.FUNC_TYPE.templatename=NULL;
    res->d.FUNC_TYPE.ret=template_expand_vde(expand, vde->d.FUNC_TYPE.ret, ifexpand);
    res->d.FUNC_TYPE.name=vde->d.FUNC_TYPE.name;
    res->d.FUNC_TYPE.body=vde->d.FUNC_TYPE.body; // TODO: fix body Typename expand
    return res;
  }
}

/* Expand var_type. This is mainly used in type check. */
struct var_type * template_expand_vt(struct var_type * expand, struct var_type * vt){
  struct var_type * res = new_var_type_ptr();
  int ifexpand = vt->left_type==T_TYPENAME_TEMPLATE;
  if(ifexpand){
    res -> left_type = expand->left_type;
  }
  else{
    res -> left_type = vt->left_type;
  }
  res -> vde = template_expand_vde(expand,vt->vde,ifexpand);
  return res;
}

/* Expand var_type_list. This is mainly used in type check. */
struct var_type_list * template_expand_vtl(struct var_type * expand, struct var_type_list * vtl){
  if(vtl==NULL) return NULL;
  struct var_type_list * res = new_var_type_list_ptr();
  res -> vt = template_expand_vt(expand, vtl->vt);
  res -> next = template_expand_vtl(expand,vtl->next);
  return res;
}


/* Test the whether the polymorphic function can be expanded as limited copies. */
int polymorphic_expansion_test(){
  struct var_type * main_vt=vtable_find_char(get_global_vtable(),"main")->vt;
  if(main_vt==NULL){
    printf("[Warning][Polymorphic expansion test] No \"main\" Function!");
    return 1;
  }
  if(main_vt->vde->t!=T_FUNC_TYPE){
    printf("[Warning][Polymorphic expansion test] \"main\" is not a function!");
    return 1;
  }
  if(main_vt->vde->d.FUNC_TYPE.templatename!=NULL){
    printf("[Warning][Polymorphic expansion test] \"main\" should not be a polymorphic function!");
    return 1;
  }
  // initialize polumorphic expansion test stack.
  PFE_visit_function(main_vt);
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

/* print given expr_list as arguments of calling functions. */
void print_expr_list_as_argument_types(struct expr_list * args) {
  if (args == NULL) {
    return;
  }
  indent ++;
  print_spaces();
  printf("Argument:");
  print_expr(args -> e);
  putchar('\n');
  indent --;
  print_expr_list_as_argument_types(args -> next);
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
  printf("Left type: ");
  switch(vt->left_type){
    case T_TYPENAME_INT:
      printf("int\n");
      break;
    case T_TYPENAME_TEMPLATE:
      printf("%s\n",vt->vde->d.FUNC_TYPE.templatename);
      break;
  }
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
    print_expr_list_as_argument_types(e -> d.FUNC.args);
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
  case T_PROC:
    pprintf("Process:\n");
    indent ++;
    pprintf("Process Head:");
    print_expr(c -> d.PROC.proc);
    putchar('\n');
    pprintf("Process Args:\n");
    print_expr_list_as_argument_types(c -> d.PROC.args);
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

/* print given cmd_list. */
void print_cmd_list(struct cmd_list * cl){
  if(cl==NULL){
    return;
  }
  print_cmd(cl->c);
  print_cmd_list(cl->next);
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

