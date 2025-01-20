#include <stdlib.h>
#include <string.h>
#include "../include/parse_printf.h"

int main(int argc, char* argv[]) {

  if (argc != 2) {
    fprintf(stderr, "usage: %s <args>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  size_t is_valid = parse(argv[1]);

  switch (is_valid) {
    case 0:
      fprintf(stderr, "main: not valid printf statement\n");
      exit(EXIT_FAILURE);
    case 1:
      printf("%s is a correct printf statement\n", argv[1]);
      exit(EXIT_SUCCESS);
  }
  

 
  return EXIT_SUCCESS;
}
