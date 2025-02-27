#include <stdio.h>
#include "util.h"  


static inline void print_usage(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage(argv);
    return EXIT_FAILURE;
  }
  char *path = argv[1];
  char *contents = file_contents(path);

  if (contents) {
   printf("Contents of %s:\n---\n\"%s\"\n---\n", path, contents);
    node_t expr;
    error_t err = parse_expr(contents, &expr);
    free(contents);
  }
  

  return EXIT_SUCCESS;
}

static inline void print_usage(char **argv) {
  printf("USAGE: %s <path>\n", argv[0]);
}
