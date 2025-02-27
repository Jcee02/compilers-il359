#include "util.h"
#include <stdio.h>


void print_error(error_t error) {
  if (error.type == ERROR_NONE) {
    return;
  }
  printf("ERROR: ");
  assert(ERROR_MAX == 6);
  switch(error.type) {
    default:
      printf("Unknown error type...");
      break;
    case ERROR_TODO:
      printf("TODO (not implemented)");
      break;
    case ERROR_SYNTAX:
      printf("Invalid syntax");
      break;
    case ERROR_TYPE:
      printf("Mismatched types");
      break;
    case ERROR_ARGS:
      printf("Invalid arguments");
      break;
    case ERROR_GEN:
      break;
    case ERROR_NONE:
      break;
  }
  putchar('\n');
  if (error.msg) {
    printf("     : %s\n", error.msg);
  }
}
long file_sz(FILE* file) {
  if (!file) {
    return 0;
  }
  fpos_t org = 0;
  if (fgetpos(file, &org) != 0) {
    fprintf(stderr, "fgetpos() failed\n");
    return 0;
  }
  fseek(file, 0, SEEK_END);
  long out = ftell(file);
  if (fsetpos(file, &org) != 0){
    fprintf(stderr, "fsetpos failed\n");
    return 0;
  }
  return out;
} 

char *file_contents(char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "Could not open file at path: %s\n", path);
    return NULL;
  }
  long size = file_sz(file);
  char *contents = malloc(size+1);
  char* write_this = contents;
  size_t bytes_read = 0;
  while (bytes_read < size) {
    size_t bytes_read_this_iteration = fread(write_this, 1, size - bytes_read, file);
    if (ferror(file)) {
      printf("Error while reading");
      free(contents);
      return NULL;
    }
    bytes_read += bytes_read_this_iteration;
    write_this += bytes_read_this_iteration;

    if (feof(file)) {
      break;
    }
  }
  contents[bytes_read] = '\0';
  return contents;
}

error_t ok = { ERROR_NONE, NULL };
const char* ws = " \r\n";
const char* delim = " \r\n,():{}=<>*";
const char* prefixes = "()'`";

token_type determine_token_type(const char* begin, size_t len) {
    char temp[256];
    if (len >= sizeof(temp)) {
        return ID;
    }
    
    strncpy(temp, begin, len);
    temp[len] = '\0';
    
    // Check for single-char tokens first
    if (len == 1) {
        switch(temp[0]) {
            case '(': return OPENPAREN;
            case ')': return CLOSINGPAREN;
            case '+': return OP_ADD;
            case '-': return OP_SUB;
            case '*': return OP_MULT;
            case '/': return OP_DIV;
            case ',': return COMMA;
            case ':': return COLON;
            case '=': return ASSIGN;
            case '<': return OP_LT;
            case '{': return OPENBRACKET;
            case '}': return CLOSINGBRACKET;
        }
    }

    // Check for two-character operators
    if (len == 2) {
        if (temp[0] == '<' && temp[1] == '<') return OP_LSHIFT;
    }

    // Check if it's a number
    char* endptr;
    strtol(temp, &endptr, 10);
    if (endptr == temp + len) {
        return INT;
    }
    
    strtod(temp, &endptr);
    if (endptr == temp + len) {
        return FLOAT;
    }

    // Check for keywords
    if (strcmp(temp, "if") == 0) return IF;
    if (strcmp(temp, "else") == 0) return ELSE;
    if (strcmp(temp, "while") == 0) return WHILE;
    if (strcmp(temp, "for") == 0) return FOR;
    if (strcmp(temp, "return") == 0) return RETURN;
    
    // If nothing else matches, it's an identifier
    return ID;
}

error_t lex(char *src, token_t *token, char **begin, char **end) {
    error_t err = ok;
    if(!src || !begin || !end || !token) {
        char *msg = "Invalid arguments to lex";
        err.type = ERROR_ARGS;
        err.msg = msg;
        return err;
    }
    
    *begin = src;
    *begin += strspn(*begin, ws);  // Skip whitespace
    *end = *begin;
    
    if (**end == '\0') {
        token->type = EOF_TOKEN;
        token->value = NULL;
        return err;
    }
    
    // Handle two-character operators
    if ((*begin)[0] == '<' && (*begin)[1] == '<') {
        *end = *begin + 2;
    } else {
        *end += strcspn(*begin, delim);
        if (*end == *begin) {
            *end += 1;
        }
    }
    
    size_t len = *end - *begin;
    token->type = determine_token_type(*begin, len);
    
    // Allocate and copy token value
    token->value = malloc(len + 1);
    if (!token->value) {
        err.type = ERROR_GEN;
        err.msg = "Memory allocation failed";
        return err;
    }
    strncpy(token->value, *begin, len);
    token->value[len] = '\0';
    
    return err;
}

error_t parse_expr(char *src, node_t *res) {
    char *beg = src;
    char *end = src;
    error_t err = ok;
    token_t token;
    
    while ((err = lex(end, &token, &beg, &end)).type == ERROR_NONE) {
        if (token.type == EOF_TOKEN) {
            break;
        }
        
        // Print token information 
        printf("Token: %-10s | Type: %d\n", token.value, token.type);
        free(token.value);  // Clean up allocated token value
    }
    return err;
}

// @return STATUS_SUCCESS upon success.
status_t valid_id(char *id) {
  return strpbrk(id, delim) == NULL ? 0 : 1;
}
