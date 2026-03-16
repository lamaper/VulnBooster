void *av_malloc(size_t size)

{

    void *ptr = NULL;


    long diff;




     

    if (size > (max_alloc_size - 32))

        return NULL;


    ptr = malloc(size + ALIGN);

    if (!ptr)

        return ptr;

    diff              = ((~(long)ptr)&(ALIGN - 1)) + 1;

    ptr               = (char *)ptr + diff;

    ((char *)ptr)[-1] = diff;


    if (size)  

    if (posix_memalign(&ptr, ALIGN, size))

        ptr = NULL;


    ptr = _aligned_malloc(size, ALIGN);



    ptr = memalign(ALIGN, size);


    ptr = memalign(size, ALIGN);



    ptr = malloc(size);


    if(!ptr && !size) {

        size = 1;

        ptr= av_malloc(1);

    }


    if (ptr)

        memset(ptr, 0x2a, size);


    return ptr;

}
