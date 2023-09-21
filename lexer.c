#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

void print_tokens(Token *tokens){
  size_t i = 0;
  while(tokens[i].type != END_OF_TOKENS){
    printf("value: %s -> ", tokens[i].value);
    switch(tokens[i].type){
      case EXIT:
        printf("type: EXIT\n");
        break;
      case OPEN_PAREN:
        printf("type: OPEN PARENTHESIS\n");
        break;
      case CLOSE_PAREN:
        printf("type: CLOSE PARENTHESIS\n");
        break;
      case INT_LIT:
        printf("type: INTEGER LITERAL\n");
        break;
      case IDENTIFIER:
        printf("type: IDENTIFIER\n");
        break;
      case SEMI:
        printf("type: SEMICOLON\n");
        break;
      case END_OF_TOKENS:
        printf("type: END OF TOKENS\n");
        break;
    }
    i++;
  }
}


void push_token(Token *token_stack, int *token_stack_size, Token *token){
  token_stack[*token_stack_size] = *token;
  (*token_stack_size)++;
}

Token *pop_token(Token *token_stack, int *token_stack_size){
  Token *result = malloc(sizeof(Token));
  *result = token_stack[*token_stack_size - 1];
  (*token_stack_size)--;
  return result;
}

Token *peek_token(Token *token_stack, int *token_stack_size){
  return &token_stack[*token_stack_size - 1];
}

Token *init_token(TokenType type, char *value){
  Token *token = malloc(sizeof(Token));
  token->type = type;
  token->value = value;
  return token;
}

Token *init_single_token(TokenType type, const char value){
  Token *token = malloc(sizeof(Token));
  token->type = type;
  char *return_value = malloc(sizeof(char) * 4);
  return_value[0] = value;
  return_value[1] = '\0';
  token->value = return_value;
  return token;
}

Token *generate_number(const char *current, size_t *index){
  char *value = malloc(sizeof(char) * 16);
  int value_index = 0;
  while(isdigit(current[*index]) && current[*index] != '\0'){
    value[value_index] = current[*index];
    value_index++;
    *index += 1;
  }
  value[value_index] = '\0';
  Token *token = init_token(INT_LIT, value);
  return token;
}

Token *generate_word(const char *current, size_t *index){
  char *value = malloc(sizeof(char) * 16);
  int value_index = 0;
  while(isalpha(current[*index]) && current[*index] != '\0'){
    value[value_index] = current[*index];
    value_index++;
    *index += 1;
  }
  value[value_index] = '\0';
  Token *token;
  if(strcmp(value, "exit") == 0){
    token = init_token(EXIT, value);
  } else {
    token = init_token(IDENTIFIER, value);
  }
  return token;
}

Token *lex_file(const char *file_name, Token *token_stack, int *token_stack_size){
  FILE *file = fopen(file_name, "r");
  int length;


  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *current = malloc(sizeof(char)*length);
  fread(current, 1, length, file);
  
  fclose(file);

  current[length] = '\0';

  for(size_t i = 0; i < length; i++){
    Token *token = NULL;
    if(isalpha(current[i])){
      token = generate_word(current, &i);
      i--;
    } else if(isdigit(current[i])){
      token = generate_number(current, &i);
      i--;
    } else if(current[i] == '('){
      token = init_single_token(OPEN_PAREN, current[i]);
    } else if(current[i] == ')'){
      token = init_single_token(CLOSE_PAREN, current[i]);
    } else if(current[i] == ';'){
      token = init_single_token(SEMI, current[i]);
    } 
    if(token != NULL){
      push_token(token_stack, token_stack_size, token);
    }
  }
  push_token(token_stack, token_stack_size, init_token(END_OF_TOKENS, "\0"));
  free(current);
  return token_stack;
}
