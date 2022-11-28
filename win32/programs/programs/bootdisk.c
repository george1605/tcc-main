#include <stdio.h>
#include <windows.h>

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        puts("Format: bootdisk <filename> <disk>");
        return 1;
    }
    FILE* fp = fopen(argv[1], "r");
    int ft = ftell(fp);
    if(ft < 512)
    {
        puts("The file provided is not a bootable image");
        return 1;
    }
    char* memory = malloc(ft + 1);
    char dsk[10] = "//./";
    long bytes_wr = 0;
    memory[510] = 0xAA;
    memory[511] = 0x55;
    memory[ft] = 0;
    OFSTRUCT buffer;
    HFILE hfile = OpenFile(strcat(dsk, argv[2]), &buffer, OF_READ);
    WriteFile(hfile, &memory, ft, &bytes_wr, NULL);
    return 0;
}