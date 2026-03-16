static inline PageDesc *page_find_alloc(target_ulong index)

{

    PageDesc **lp, *p;


     

    if (index > ((target_ulong)L2_SIZE * L1_SIZE))

        return NULL;


    lp = &l1_map[index >> L2_BITS];

    p = *lp;

    if (!p) {


        unsigned long addr;

        size_t len = sizeof(PageDesc) * L2_SIZE;

         

        p = mmap(0, len, PROT_READ | PROT_WRITE,

                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        *lp = p;

        addr = h2g(p);

        if (addr == (target_ulong)addr) {

            page_set_flags(addr & TARGET_PAGE_MASK,

                           TARGET_PAGE_ALIGN(addr + len),

                           PAGE_RESERVED); 

        }


        p = qemu_mallocz(sizeof(PageDesc) * L2_SIZE);

        *lp = p;


    }

    return p + (index & (L2_SIZE - 1));

}
