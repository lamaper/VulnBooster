static bool tb_invalidate_phys_page(tb_page_addr_t addr, uintptr_t pc)

{

    TranslationBlock *tb;

    PageDesc *p;

    int n;


    TranslationBlock *current_tb = NULL;

    CPUState *cpu = current_cpu;

    CPUArchState *env = NULL;

    int current_tb_modified = 0;

    target_ulong current_pc = 0;

    target_ulong current_cs_base = 0;

    uint32_t current_flags = 0;




    assert_memory_lock();



    addr &= TARGET_PAGE_MASK;

    p = page_find(addr >> TARGET_PAGE_BITS);

    if (!p) {

        return false;

    }



    tb_lock();

    tb = p->first_tb;


    if (tb && pc != 0) {

        current_tb = tb_find_pc(pc);

    }

    if (cpu != NULL) {

        env = cpu->env_ptr;

    }


    while (tb != NULL) {

        n = (uintptr_t)tb & 3;

        tb = (TranslationBlock *)((uintptr_t)tb & ~3);


        if (current_tb == tb &&

            (current_tb->cflags & CF_COUNT_MASK) != 1) {

                 



            current_tb_modified = 1;

            cpu_restore_state_from_tb(cpu, current_tb, pc);

            cpu_get_tb_cpu_state(env, &current_pc, &current_cs_base,

                                 &current_flags);

        }


        tb_phys_invalidate(tb, addr);

        tb = tb->page_next[n];

    }

    p->first_tb = NULL;


    if (current_tb_modified) {

         

        tb_gen_code(cpu, current_pc, current_cs_base, current_flags,

                    1 | curr_cflags());

         

        return true;

    }


    tb_unlock();



    return false;

}
