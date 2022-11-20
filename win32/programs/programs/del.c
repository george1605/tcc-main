#include <stdio.h>

int exists(const char* pathname)
{
  FILE* fp = fopen(pathname, "r");
  if(!fp)
  {
    return 0;
  }else {
    fclose(fp);
    return 1;
  }
}

int main(int argc, char** argv) {
  if(argc < 2)
    perror("Format: ./del <pathname>");
  if(exists(argv[1]))
    if (remove(argv[1]) == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("The file is not deleted.");
    }
    return 0;
}