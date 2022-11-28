#include "serialise.h"

int main()
{
    int p;
    deserialise(TYPE_INT, &p, "121");
    printf("%i", p);
}