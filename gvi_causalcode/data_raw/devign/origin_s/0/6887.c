void *av_malloc(unsigned int size)

{

    void *ptr;


    ptr = memalign(16,size);


    ptr = malloc(size);


    return ptr;

}
