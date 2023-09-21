#ifndef LEXER_H_
#define LEXER_H_

#define MAX_TOKEN_LENGTH 1024

typedef enum {
  EXIT,
  OPEN_PAREN,
  CLOSE_PAREN,
  INT_LIT,
  IDENTIFIER,
  SEMI,
  END_OF_TOKENS
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

void print_tokens(Token *tokens);
void push_token(Token *token_stack, int *token_stack_size, Token *token);
Token *pop_token(Token *token_stack, int *token_stack_size);
Token *peek_token(Token *token_stack, int *token_stack_size);
Token *init_token(TokenType type, char *value);
Token *init_single_token(TokenType type, char value);
Token *generate_number(const char *current, size_t *index);
Token *generate_word(const char *current, size_t *index);
Token *lex_file(const char *file_name, Token *token_stack, int *token_stack_size);

#endif
