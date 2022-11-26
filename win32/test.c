#include "serialise.h"

int main()
{
    int p;
    deserialise(TYPE_INT, &p, "123");
    printf("%i", p);
}