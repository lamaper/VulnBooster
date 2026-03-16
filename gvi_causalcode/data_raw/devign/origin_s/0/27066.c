void *av_realloc(void *ptr, size_t size)

{


    int diff;




     

    if (size > (MAX_MALLOC_SIZE-16))

        return NULL;


     

    if(!ptr) return av_malloc(size);

    diff= ((char*)ptr)[-1];

    return (char*)realloc((char*)ptr - diff, size + diff) + diff;


    return realloc(ptr, size + !size);


}
