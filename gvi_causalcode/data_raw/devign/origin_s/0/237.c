void *av_realloc(void *ptr, unsigned int size)

{


    int diff;




     

    if(size > INT_MAX)

        return NULL;


     

    if(!ptr) return av_malloc(size);

    diff= ((char*)ptr)[-1];

    return realloc(ptr - diff, size + diff) + diff;


    return realloc(ptr, size);


}
