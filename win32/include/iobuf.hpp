#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

template<typename T=uint8_t>
class iobuf {
private:
    T* ptr;
    size_t c, siz;
public:
    iobuf(int size)
    {
        this->ptr = (T*)malloc(sizeof(T) * size);
        this->c = 0;
        this->siz = size;
    }
    ~iobuf()
    {
        if(this->ptr)
            free(this->ptr);
    }
    void read(FILE* f, size_t siz)
    {
        fread(this->ptr, sizeof(T), siz, f);
        c += siz;
    }
    void read(size_t size)
    {
        read(stdin, size);
    }
    void clear()
    {
        memset(this->ptr, 0, siz);
        this->c = 0;
    }
    void push(T value)
    {
        this->c++;
        this->ptr[c] = value;
    }
    T pop()
    {
        T p = this->ptr[c--];
        return p;
    }
    void write(FILE* fp, size_t siz)
    {
        fwrite(this->ptr, sizeof(T), siz, fp);
    }
    void write(size_t siz)
    {
        write(stdout, siz);
    }
};