void cpu_reset(CPUSPARCState *env)

{

    if (qemu_loglevel_mask(CPU_LOG_RESET)) {

        qemu_log("CPU Reset (CPU %d)\n", env->cpu_index);

        log_cpu_state(env, 0);

    }



    tlb_flush(env, 1);

    env->cwp = 0;


    env->wim = 1;


    env->regwptr = env->regbase + (env->cwp * 16);



    env->cleanwin = env->nwindows - 2;

    env->cansave = env->nwindows - 2;

    env->pstate = PS_RMO | PS_PEF | PS_IE;

    env->asi = 0x82;  




    env->psret = 0;


    env->psrs = 1;

    env->psrps = 1;

    CC_OP = CC_OP_FLAGS;


    env->pstate = PS_PRIV;

    env->hpstate = HS_PRIV;

    env->tsptr = &env->ts[env->tl & MAXTL_MASK];

    env->lsu = 0;


    env->mmuregs[0] &= ~(MMU_E | MMU_NF);

    env->mmuregs[0] |= env->def->mmu_bm;


    env->pc = 0;

    env->npc = env->pc + 4;


}
