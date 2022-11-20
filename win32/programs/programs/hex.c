#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 1)
    return -1;
  unsigned char buf[100];
  size_t p;
  FILE *fp = fopen(argv[1], "rb");
  while (fread(buf, 1, 100, fp)) {
    for (p = 0; p < 100; p++) {
        printf("%X ", buf[p]);
    }
    memset(buf, 0, 100);
  }
  return 0;
}