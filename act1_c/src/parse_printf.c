#include "../include/parse_printf.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

size_t parse(char* arg) {
  char* fn = strtok(arg, "(");
  bool is_closed_paren = false;
  if (strcmp(arg, "printf") != 0)
    return 0;
  

  char* lt = strtok(NULL, ")");
  if (!lt) 
    return 0;

  is_closed_paren = true;
  
  char* sc = strtok(NULL, ";");

  if (sc == NULL && is_closed_paren)
    return 1;

  return 0;
}


