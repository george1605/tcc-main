#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CELLS 30000

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: brainf <file>\n");
    return 1;
  }

  FILE* fp = fopen(argv[1], "r");
  int sz = ftell(fp);
  rewind(fp);
  char* program = malloc(sz + 1);
  fread(program, 1, 99, fp);
  char cells[NUM_CELLS] = {0};
  memset(cells, NUM_CELLS, 0);
  char *ptr = cells;

  for (int i = 0; program[i] != '\0'; i++) {
    char c = program[i];
    switch (c) {
      case '>':
        ptr++;
        break;
      case '<':
        ptr--;
        break;
      case '+':
        (*ptr)++;
        break;
      case '-':
        (*ptr)--;
        break;
      case '.':
        putchar(*ptr);
        break;
      case ',':
        *ptr = getchar();
        break;
      case '[':
        if (*ptr == 0) {
          int bracket_count = 1;
          while (bracket_count > 0) {
            i++;
            c = program[i];
            if (c == '[') {
              bracket_count++;
            } else if (c == ']') {
              bracket_count--;
            }
          }
        }
        break;
      case ']':
        if (*ptr != 0) {
          int bracket_count = 1;
          while (bracket_count > 0) {
            i--;
            c = program[i];
            if (c == '[') {
              bracket_count--;
            } else if (c == ']') {
              bracket_count++;
            }
          }
          i--;
        }
        break;
      default:
        break;
    }
  }

  return 0;
}