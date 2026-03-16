void cpu_ppc_reset (void *opaque)

{

    CPUPPCState *env;

    target_ulong msr;



    env = opaque;

    msr = (target_ulong)0;


    msr |= (target_ulong)0 << MSR_HV;  


    msr |= (target_ulong)0 << MSR_AP;  

    msr |= (target_ulong)0 << MSR_SA;  

    msr |= (target_ulong)1 << MSR_EP;


     

    msr |= (target_ulong)1 << MSR_SE;

    msr |= (target_ulong)1 << MSR_BE;



    msr |= (target_ulong)1 << MSR_FP;  

    msr |= (target_ulong)1 << MSR_PR;


    env->nip = env->hreset_vector | env->excp_prefix;

    if (env->mmu_model != POWERPC_MMU_REAL_4xx)

        ppc_tlb_invalidate_all(env);


    env->msr = msr;

    hreg_compute_hflags(env);

    env->reserve = -1;

     

    env->pending_interrupts = 0;

    env->exception_index = POWERPC_EXCP_NONE;

    env->error_code = 0;

     

    tlb_flush(env, 1);

}
