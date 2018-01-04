#include <stdio.h>  /* printf */
#include <stdlib.h> /* free */
#include <dlfcn.h>
#include "../../inc/vector.h"

int ElementPrintInt(void* _element, void* _context)
{
    printf("%d ", *(int*)_element);
/*    printf("%x ", _element);*/
    return 1;
}

int ElementPrintChar(void* _element, void* _context)
{
    printf("%c ", *(char*)_element);
    return 1;
}

int ElementPrintStr(void* _element, void* _context)
{
    puts(*(char**)_element);
    return 1;
}

int destroyIntElement(void* _element, void* _context)
{
    free(_element);
    /*_element = NULL;*/
    return 1;
}

int main()
{
    void* handle;
    Vector*(*Create)(size_t, size_t);
    void(*Destroy)(Vector**, VectorElementAction);
    ADTErr (*Append)(Vector*, void*);
    size_t (*ForEach)(const Vector*, VectorElementAction, void*);
    Vector* vector = NULL;
    
    int* pa;
    
    pa = malloc(sizeof(int));
    *pa = 1024;
    
    handle = dlopen("libVector.so", RTLD_LAZY);
    if(!handle)
    {
        printf("something got wrong\n");
        exit(1);
    }
    
    Create = dlsym(handle, "VectorCreate");
    Destroy = dlsym(handle, "VectorDestroy");
    Append = dlsym(handle, "VectorAppend");
    ForEach = dlsym(handle, "VectorForEach");
    
    vector = Create(4, 2);
    Append(vector, pa);
    ForEach(vector, ElementPrintInt, NULL);
    printf("\n");
    Destroy(&vector, NULL);

    
    dlclose(handle);
    return 0;
}
/* compile with:
gcc -rdynamic -o testDyn rdyn.c -LlibVector -ldl
*/
