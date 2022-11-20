#include <stdio.h>

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    perror("Format: ./touch.o <filename>");
    return 1;
  }
  FILE* fp = fopen(argv[1], "x");
  fclose(fp);
}