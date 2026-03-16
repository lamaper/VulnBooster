void cpu_reset(CPUSPARCState *env)

{

    tlb_flush(env, 1);

    env->cwp = 0;

    env->wim = 1;

    env->regwptr = env->regbase + (env->cwp * 16);


    env->user_mode_only = 1;


    env->cleanwin = env->nwindows - 2;

    env->cansave = env->nwindows - 2;

    env->pstate = PS_RMO | PS_PEF | PS_IE;

    env->asi = 0x82;  



    env->psret = 0;

    env->psrs = 1;

    env->psrps = 1;


    env->pstate = PS_PRIV;

    env->hpstate = HS_PRIV;

    env->pc = 0x1fff0000020ULL;  

    env->tsptr = &env->ts[env->tl];


    env->pc = 0;

    env->mmuregs[0] &= ~(MMU_E | MMU_NF);

    env->mmuregs[0] |= env->mmu_bm;


    env->npc = env->pc + 4;


}
