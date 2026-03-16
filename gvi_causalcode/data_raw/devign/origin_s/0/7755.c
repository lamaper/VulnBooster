void HELPER(mvpg)(CPUS390XState *env, uint64_t r0, uint64_t r1, uint64_t r2)

{

     

    env->cc_op = 0;


    memmove(g2h(r1), g2h(r2), TARGET_PAGE_SIZE);


    mvc_fast_memmove(env, TARGET_PAGE_SIZE, r1, r2);


}
