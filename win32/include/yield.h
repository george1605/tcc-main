#include <string.h>
#include <stdlib.h>
#define ARR_SIZE(x, type) sizeof(x) / sizeof(type)
#define YIELD_OVERFLOW -128

static void* _yieldStack[100];
static int _yieldNo = 0;
int _yieldError = 0;

void _yield(void* ptr)
{
    if(_yieldNo++ > ARR_SIZE(_yieldStack, void*))
        {
            _yieldError = YIELD_OVERFLOW;
            return;
        }
    _yieldStack[_yieldNo] = ptr;
}

void _clryield()
{
    memset(_yieldStack, 0, sizeof _yieldStack);
}