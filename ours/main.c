#include <stdio.h>
#include "lang.h"
#include "lexer.h"
#include "parser.h"

extern struct cmd_list * root;
int yyparse();

int main(int argc, char * * argv) {
  if (argc == 1) {
    printf("[Error][main.c] Not enough arguments!\n");
    return 0;
  }
  if (argc >= 3) {
    printf("[Error][main.c] Too many arguments!\n");
    return 0;
  }
  yyin = fopen(argv[1], "rb");
  if (yyin == NULL) {
    printf("[Error][main.c] File %s can't be opened.\n", argv[1]);
    return 0;
  }
  printf("[Info][main.c] Let's do yyparser! This is the grammar tree with polymorphic functions.\n");
  // Firstly initialize variable table!
  init_global_vtable();
  // Do yyparse!
  yyparse();
  fclose(yyin);
  // Print grammar tree.
  print_cmd_list(root);
  printf("[Info][main.c] Then we'll test if the polymorphic function can be expanded as limited copies. \n");
  // Polymorphic expansion test.
  polymorphic_expansion_test(root);
  printf("[Info][main.c] Test pass and the updated grammar tree is below. \n");
  set_template_output(0);
  print_cmd_list(root);
  
  return 0;
}