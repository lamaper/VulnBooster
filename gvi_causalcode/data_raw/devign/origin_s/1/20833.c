void *av_malloc(unsigned int size)

{

    void *ptr = NULL;


    long diff;




     

    if(size > (INT_MAX-16) )

        return NULL;


    ptr = malloc(size+16);

    if(!ptr)

        return ptr;

    diff= ((-(long)ptr - 1)&15) + 1;

    ptr = (char*)ptr + diff;

    ((char*)ptr)[-1]= diff;


    posix_memalign(&ptr,16,size);


    ptr = memalign(16,size);


    ptr = malloc(size);


    return ptr;

}
