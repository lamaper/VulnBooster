static inline void do_rfi(CPUPPCState *env, target_ulong nip, target_ulong msr,
                          target_ulong msrm, int keep_msrh)
{
    CPUState *cs = CPU(ppc_env_get_cpu(env));

    if (msr_is_64bit(env, msr)) {
        nip = (uint64_t)nip;
        msr &= (uint64_t)msrm;
    } else {
        nip = (uint32_t)nip;
        msr = (uint32_t)(msr & msrm);
        if (keep_msrh) {
            msr |= env->msr & ~((uint64_t)0xFFFFFFFF);
        }
    }

    nip = (uint32_t)nip;
    msr &= (uint32_t)msrm;

     
    env->nip = nip & ~((target_ulong)0x00000003);
    hreg_store_msr(env, msr, 1);

    cpu_dump_rfi(env->nip, env->msr);

     
    cs->interrupt_request |= CPU_INTERRUPT_EXITTB;
}