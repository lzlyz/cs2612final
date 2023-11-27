#include <stdio.h>
#include "lang.h"
#include "lexer.h"
#include "parser.h"

extern struct cmd * root;
int yyparse();

int main(int argc, char * * argv) {
  if (argc == 1) {
    printf("Error, not enough arguments!\n");
    return 0;
  }
  if (argc >= 3) {
    printf("Error, too many arguments!\n");
    return 0;
  }
  yyin = fopen(argv[1], "rb");
  if (yyin == NULL) {
    printf("File %s can't be opened.\n", argv[1]);
    return 0;
  }
  printf("Let's Go\n");
  yyparse();
  fclose(yyin);
  print_cmd(root);
}