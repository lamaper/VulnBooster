void av_free(void *ptr)

{


    if (ptr)

        free((char *)ptr - ((char *)ptr)[-1]);


    _aligned_free(ptr);


    free(ptr);


}
