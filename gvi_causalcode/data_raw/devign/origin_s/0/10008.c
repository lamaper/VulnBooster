void tlb_flush(CPUState *env, int flush_global)

{

    int i;


    printf("tlb_flush:\n");


     

    env->current_tb = NULL;



    for(i = 0; i < CPU_TLB_SIZE; i++) {

        env->tlb_table[0][i].addr_read = -1;

        env->tlb_table[0][i].addr_write = -1;

        env->tlb_table[0][i].addr_code = -1;

        env->tlb_table[1][i].addr_read = -1;

        env->tlb_table[1][i].addr_write = -1;

        env->tlb_table[1][i].addr_code = -1;


        env->tlb_table[2][i].addr_read = -1;

        env->tlb_table[2][i].addr_write = -1;

        env->tlb_table[2][i].addr_code = -1;


        env->tlb_table[3][i].addr_read = -1;

        env->tlb_table[3][i].addr_write = -1;

        env->tlb_table[3][i].addr_code = -1;



    }



    memset (env->tb_jmp_cache, 0, TB_JMP_CACHE_SIZE * sizeof (void *));


    if (env->kqemu_enabled) {

        kqemu_flush(env, flush_global);

    }


    tlb_flush_count++;

}
