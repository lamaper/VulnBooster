static inline void *alloc_code_gen_buffer(void)

{

    int flags = MAP_PRIVATE | MAP_ANONYMOUS;

    uintptr_t start = 0;

    size_t size = tcg_ctx.code_gen_buffer_size;

    void *buf;



     

    flags |= MAP_32BIT;

     

    if (size > 800u * 1024 * 1024) {

        tcg_ctx.code_gen_buffer_size = size = 800u * 1024 * 1024;

    }


    start = 0x40000000ul;


    start = 0x90000000ul;



    start = 0x128000000ul;


    start = 0x08000000ul;





    buf = mmap((void *)start, size + qemu_real_host_page_size,

               PROT_NONE, flags, -1, 0);

    if (buf == MAP_FAILED) {

        return NULL;

    }


    if (cross_256mb(buf, size)) {

         

        size_t size2;

        void *buf2 = mmap(NULL, size + qemu_real_host_page_size,

                          PROT_NONE, flags, -1, 0);

        switch (buf2 != MAP_FAILED) {

        case 1:

            if (!cross_256mb(buf2, size)) {

                 

                munmap(buf, size);

                break;

            }

             

            munmap(buf2, size);

             

        default:

             

            buf2 = split_cross_256mb(buf, size);

            size2 = tcg_ctx.code_gen_buffer_size;

            if (buf == buf2) {

                munmap(buf + size2 + qemu_real_host_page_size, size - size2);

            } else {

                munmap(buf, size - size2);

            }

            size = size2;

            break;

        }

        buf = buf2;

    }




     

    mprotect(buf, size, PROT_WRITE | PROT_READ | PROT_EXEC);



     

    qemu_madvise(buf, size, QEMU_MADV_HUGEPAGE);



    return buf;

}
