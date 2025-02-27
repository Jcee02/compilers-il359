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
const char* delim = " \r\n,():";
const char* prefixes = "()\'`";

error_t lex(char *src, char **begin, char **end) {
  error_t err = ok;
  if(!src || !begin || !end) {
    char *msg = "Can not lex empty source file";
    ERROR_PREP(err, ERROR_ARGS, msg);
    return err;
  }
  *begin = src;
  /*
    get sz of subset of src containing ws elements 
    and add it to memory address of begin to ignore all ws elements 
  */
  *begin += strspn(*begin, ws);
  *end = *begin;
  if (**end == '\0') {
    return err;
  }
  *end += strcspn(*begin, delim);
  if (*end == *begin) {
    *end += 1;
  }

  return err;
}

error_t parse_expr(char *src, node_t *res) {
  char *beg = src;
  char *end = src;
  error_t err = ok;
  while ((err = lex(end, &beg, &end)).type == ERROR_NONE) {
    if (end - beg == 0) {
      break;
    }
    printf("lexed: %.*s\n", end - beg, beg);

  }
  return err;
}

// @return STATUS_SUCCESS upon success.
status_t valid_id(char *id) {
  return strpbrk(id, delim) == NULL ? 0 : 1;
}
