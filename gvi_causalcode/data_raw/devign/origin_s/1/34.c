static inline void do_rfi(CPUPPCState *env, target_ulong nip, target_ulong msr)

{

    CPUState *cs = CPU(ppc_env_get_cpu(env));



     

    msr &= ~(1ULL << MSR_POW);


     

    if (!msr_is_64bit(env, msr)) {

        nip = (uint32_t)nip;

    }


    nip = (uint32_t)nip;


     

    env->nip = nip & ~((target_ulong)0x00000003);

    hreg_store_msr(env, msr, 1);


    cpu_dump_rfi(env->nip, env->msr);


     

    cs->interrupt_request |= CPU_INTERRUPT_EXITTB;



     

    check_tlb_flush(env);

}
