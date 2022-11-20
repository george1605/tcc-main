#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 1)
    return -1;
  char buf[100];
  size_t p;
  FILE *fp = fopen(argv[1], "rb");
  while (fread(buf, 1, 100, fp)) {
    for (p = 0; p < 100; p++) {
      if (isalnum(buf[p]))
        putc(buf[p], stdout);
      else
        putc('.', stdout);
    }
    memset(buf, 0, 100);
  }
  return 0;
}