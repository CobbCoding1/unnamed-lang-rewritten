#include <stdio.h>

#include "lexer.h"

int main(){
  char *filename = "./test.unn";

  Token token_stack[MAX_TOKEN_LENGTH];
  int token_stack_size = 0;

  Token *tokens = lex_file("./test.unn", token_stack, &token_stack_size);
  print_tokens(tokens);
}
