void cpu_x86_update_cr3(CPUX86State *env)

{

    if (env->cr[0] & CR0_PG_MASK) {


        printf("CR3 update: CR3=%08x\n", env->cr[3]);


        tlb_flush(env);

    }

}
