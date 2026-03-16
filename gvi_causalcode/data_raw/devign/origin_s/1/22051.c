static inline TranslationBlock *tb_find_fast(void)

{

    TranslationBlock *tb;

    target_ulong cs_base, pc;

    uint64_t flags;


    flags = env->hflags;

    flags |= (env->eflags & (IOPL_MASK | TF_MASK | VM_MASK));

    flags |= env->intercept;

    cs_base = env->segs[R_CS].base;

    pc = cs_base + env->eip;


    flags = env->thumb | (env->vfp.vec_len << 1)

            | (env->vfp.vec_stride << 4);

    if ((env->uncached_cpsr & CPSR_M) != ARM_CPU_MODE_USR)

        flags |= (1 << 6);

    if (env->vfp.xregs[ARM_VFP_FPEXC] & (1 << 30))

        flags |= (1 << 7);

    flags |= (env->condexec_bits << 8);

    cs_base = 0;

    pc = env->regs[15];



     

    flags = (((env->pstate & PS_PEF) >> 1) | ((env->fprs & FPRS_FEF) << 2))

        | (env->pstate & PS_PRIV) | ((env->lsu & (DMMU_E | IMMU_E)) >> 2);


     

    flags = (env->psref << 4) | env->psrs;


    cs_base = env->npc;

    pc = env->pc;


    flags = env->hflags;

    cs_base = 0;

    pc = env->nip;


    flags = env->hflags & (MIPS_HFLAG_TMASK | MIPS_HFLAG_BMASK);

    cs_base = 0;

    pc = env->PC[env->current_tc];


    flags = (env->fpcr & M68K_FPCR_PREC)   

            | (env->sr & SR_S)             

            | ((env->macsr >> 4) & 0xf);   

    cs_base = 0;

    pc = env->pc;


    flags = env->flags;

    cs_base = 0;

    pc = env->pc;


    flags = env->ps;

    cs_base = 0;

    pc = env->pc;


    flags = env->pregs[PR_CCS] & (U_FLAG | X_FLAG);

    cs_base = 0;

    pc = env->pc;




    tb = env->tb_jmp_cache[tb_jmp_cache_hash_func(pc)];

    if (__builtin_expect(!tb || tb->pc != pc || tb->cs_base != cs_base ||

                         tb->flags != flags, 0)) {

        tb = tb_find_slow(pc, cs_base, flags);

         

        if (tb_invalidated_flag) {

             

            T0 = 0;

        }

    }

    return tb;

}
