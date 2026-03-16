long target_mmap(target_ulong start, target_ulong len, int prot,

                 int flags, int fd, target_ulong offset)

{

    target_ulong ret, end, real_start, real_end, retaddr, host_offset, host_len;

    long host_start;


        defined(__ia64) || defined(__mips__)

    static target_ulong last_start = 0x40000000;


     

    static target_ulong last_start = 0x18000000;



    {

        printf("mmap: start=0x%lx len=0x%lx prot=%c%c%c flags=",

               start, len,

               prot & PROT_READ ? 'r' : '-',

               prot & PROT_WRITE ? 'w' : '-',

               prot & PROT_EXEC ? 'x' : '-');

        if (flags & MAP_FIXED)

            printf("MAP_FIXED ");

        if (flags & MAP_ANONYMOUS)

            printf("MAP_ANON ");

        switch(flags & MAP_TYPE) {

        case MAP_PRIVATE:

            printf("MAP_PRIVATE ");

            break;

        case MAP_SHARED:

            printf("MAP_SHARED ");

            break;

        default:

            printf("[MAP_TYPE=0x%x] ", flags & MAP_TYPE);

            break;

        }

        printf("fd=%d offset=%lx\n", fd, offset);

    }




    if (offset & ~TARGET_PAGE_MASK) {

        errno = EINVAL;

        return -1;

    }



    len = TARGET_PAGE_ALIGN(len);

    if (len == 0)

        return start;

    real_start = start & qemu_host_page_mask;



    if (!(flags & MAP_FIXED)) {


    defined(__ia64) || defined(__mips__) || defined(__CYGWIN__)

         

        if (real_start == 0) {

            real_start = last_start;

            last_start += HOST_PAGE_ALIGN(len);

        }


        if (0 && qemu_host_page_size != qemu_real_host_page_size) {

             

             

             

             

abort();

            host_len = HOST_PAGE_ALIGN(len) + qemu_host_page_size - TARGET_PAGE_SIZE;

            real_start = (long)mmap(g2h(real_start), host_len, PROT_NONE,

                                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

            if (real_start == -1)

                return real_start;

            real_end = real_start + host_len;

            start = HOST_PAGE_ALIGN(real_start);

            end = start + HOST_PAGE_ALIGN(len);

            if (start > real_start)

                munmap((void *)real_start, start - real_start);

            if (end < real_end)

                munmap((void *)end, real_end - end);

             

            flags |= MAP_FIXED;

        } else {

             

            host_offset = offset & qemu_host_page_mask;

            host_len = len + offset - host_offset;

            host_start = (long)mmap(real_start ? g2h(real_start) : NULL,

                                    host_len, prot, flags, fd, host_offset);

            if (host_start == -1)

                return host_start;

             

            if (!(flags & MAP_ANONYMOUS))

                host_start += offset - host_offset;

            start = h2g(host_start);

            goto the_end1;

        }

    }



    if (start & ~TARGET_PAGE_MASK) {

        errno = EINVAL;

        return -1;

    }

    end = start + len;

    real_end = HOST_PAGE_ALIGN(end);



     

    if (!(flags & MAP_ANONYMOUS) &&

        (offset & ~qemu_host_page_mask) != (start & ~qemu_host_page_mask)) {

         

        if ((flags & MAP_TYPE) == MAP_SHARED &&

            (prot & PROT_WRITE)) {

            errno = EINVAL;

            return -1;

        }

        retaddr = target_mmap(start, len, prot | PROT_WRITE,

                              MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS,

                              -1, 0);

        if (retaddr == -1)

            return retaddr;

        pread(fd, g2h(start), len, offset);

        if (!(prot & PROT_WRITE)) {

            ret = target_mprotect(start, len, prot);

            if (ret != 0)

                return ret;

        }

        goto the_end;

    }



     

    if (start > real_start) {

        if (real_end == real_start + qemu_host_page_size) {

             

            ret = mmap_frag(real_start, start, end,

                            prot, flags, fd, offset);

            if (ret == -1)

                return ret;

            goto the_end1;

        }

        ret = mmap_frag(real_start, start, real_start + qemu_host_page_size,

                        prot, flags, fd, offset);

        if (ret == -1)

            return ret;

        real_start += qemu_host_page_size;

    }

     

    if (end < real_end) {

        ret = mmap_frag(real_end - qemu_host_page_size,

                        real_end - qemu_host_page_size, real_end,

                        prot, flags, fd,

                        offset + real_end - qemu_host_page_size - start);

        if (ret == -1)

            return ret;

        real_end -= qemu_host_page_size;

    }



     

    if (real_start < real_end) {

        unsigned long offset1;

	if (flags & MAP_ANONYMOUS)

	  offset1 = 0;

	else

	  offset1 = offset + real_start - start;

        ret = (long)mmap(g2h(real_start), real_end - real_start,

                         prot, flags, fd, offset1);

        if (ret == -1)

            return ret;

    }

 the_end1:

    page_set_flags(start, start + len, prot | PAGE_VALID);

 the_end:


    printf("ret=0x%lx\n", (long)start);

    page_dump(stdout);

    printf("\n");


    return start;

}
