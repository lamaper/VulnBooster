target_ulong helper_rdhwr_cc(CPUMIPSState *env)

{

    check_hwrena(env, 2);


    return env->CP0_Count;


    return (int32_t)cpu_mips_get_count(env);


}
