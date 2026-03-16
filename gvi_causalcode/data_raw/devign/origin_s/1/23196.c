void *av_malloc(size_t size)

{

    void *ptr = NULL;


    long diff;




     

    if(size > (INT_MAX-32) )

        return NULL;


    ptr = malloc(size+32);

    if(!ptr)

        return ptr;

    diff= ((-(long)ptr - 1)&31) + 1;

    ptr = (char*)ptr + diff;

    ((char*)ptr)[-1]= diff;


    if (posix_memalign(&ptr,32,size))

        ptr = NULL;


    ptr = memalign(32,size);


    ptr = malloc(size);


    return ptr;

}
