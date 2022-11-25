#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
int seed = 0;
const char dice[] = "+-------+\n"
                    "|       |\n"
                    "|   %i   |\n"
                    "|       |\n"
                    "+-------+";

int rand_dice()
{
    srand(++seed);
    return (rand() % 6) + 1;
}

void print_dice(int number)
{
    system("cls");
    printf(dice, number);
}

void menu()
{
    puts("\t\tWelcome to DiceRoll\n");
    puts("\t Press the enter key to continue\n");
    while(!getc(stdin));
}

int try_again(int number)
{
    puts("\nPress enter to try again\n");
    puts("To exit, press - and enter");
    if(getc(stdin) != '-')
    {
        print_dice(number);
        return 0;
    }
    return 1;
}

int main()
{
    int c = 0;
    menu();
    print_dice(rand_dice());
    do {   
        c = try_again(rand_dice());
    } while(!c);
    return 0;
}