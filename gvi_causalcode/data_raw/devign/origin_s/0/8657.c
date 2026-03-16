static void notdirty_mem_writew(void *opaque, target_phys_addr_t ram_addr,

                                uint32_t val)

{

    int dirty_flags;

    dirty_flags = phys_ram_dirty[ram_addr >> TARGET_PAGE_BITS];

    if (!(dirty_flags & CODE_DIRTY_FLAG)) {


        tb_invalidate_phys_page_fast(ram_addr, 2);

        dirty_flags = phys_ram_dirty[ram_addr >> TARGET_PAGE_BITS];


    }

    stw_p(qemu_get_ram_ptr(ram_addr), val);


    if (cpu_single_env->kqemu_enabled &&

        (dirty_flags & KQEMU_MODIFY_PAGE_MASK) != KQEMU_MODIFY_PAGE_MASK)

        kqemu_modify_page(cpu_single_env, ram_addr);


    dirty_flags |= (0xff & ~CODE_DIRTY_FLAG);

    phys_ram_dirty[ram_addr >> TARGET_PAGE_BITS] = dirty_flags;

     

    if (dirty_flags == 0xff)

        tlb_set_dirty(cpu_single_env, cpu_single_env->mem_io_vaddr);

}
