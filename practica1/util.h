#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

# define peek_past(str, chars) (str += strspn((str), (chars)))
# define peek_until(str, chars) (str += strcspn((str), (chars)))

//ws: whitespace characters that shall be safely skipped by the lexer 
extern const char* ws;
//delim: delimiter characters that separate different tokens
extern const char* delim;
//prefix characters that may come before a token but not after
extern const char* prefixes;

typedef enum {
  INT,
  FLOAT,
  CHAR,
  VOID,
  STRING,
  ID,
  CONST,
  SEMICOLON,
  COMMA,
  OPENPAREN,
  CLOSINGPAREN,
  OPENBRACKET,
  CLOSINGBRACKET,
  ASSIGN,
  IF,
  WHILE,
  RETURN,
  ELSE,
  FOR,
  OP_ADD,
  OP_SUB,
  OP_MULT,
  OP_DIV,
  OP_LSHIFT,
  OP_RSHIFT,
  OP_LOGICAND,
  OP_LOGICOR,
  OP_GT,
  OP_LT,
  OP_GTE,
  OP_LTE,
  OP_EQ,
  OP_NEQ,
} token_type;

//status flags for boilerplate stuff, hate return 0/1, having explicit enum makes it more readable
typedef enum {
  STATUS_SUCCESS,
  STATUS_FAILURE,
} status_t;

#define ERROR_CREATE(n, t, msg) \
  error_t (n) = { (t), (msg) } 

#define ERROR_PREP(n, t, message) \
  (n).type = (t);                 \
  (n).message = (message);

//poor mans exception 
typedef struct {
  enum error_type {
    ERROR_NONE = 0,
    ERROR_ARGS,
    ERROR_TYPE,
    ERROR_GEN,
    ERROR_SYNTAX,
    ERROR_TODO,
    ERROR_MAX
  } type;

  char *msg;
} error_t;

void print_error(error_t error);

extern error_t ok;

typedef long long integer_t;

typedef struct {
  char* value;
  token_type token;
} token_t;      

typedef struct node_t {
  enum node_type {
    NODE_TYPE_NONE,
    NODE_TYPE_INTEGER,
    NODE_TYPE_PROGRAM,
    NODE_TYPE_MAX,
  } type;

  union node_value {
    integer_t integer;
  } value;
  
  //3 to support ternary operators, not only binary
  struct node_t **child;
} node_t;

/*
 when function/macro ends in p it means predicate
 we match every node type with a predicate so we dont
 write much boilerplate????
*/
#define nonep(node) ((node).type == NODE_TYPE_NONE)
#define integerp(node) ((node).type == NODE_TYPE_INTEGER)
typedef struct binding_t {
  char *id;
  node_t *value;
  struct binding_t *next;
} binding_t;

typedef struct environment_t {
  struct environment_t *parent;
  binding_t *bind;
} environment_t;


long file_sz(FILE*);
char *file_contents(char*);

//given a source, scan the next token and point to it with begin and end pointers
error_t lex(char* src, char** begin, char** end);

error_t parse_expr(char* src, node_t* res);
status_t valid_id(char* id);
#endif
