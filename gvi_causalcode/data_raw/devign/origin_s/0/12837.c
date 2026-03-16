target_ulong helper_rdhwr_cc(CPUMIPSState *env)

{

    if ((env->hflags & MIPS_HFLAG_CP0) ||

        (env->CP0_HWREna & (1 << 2))) {


        return env->CP0_Count;


        return (int32_t)cpu_mips_get_count(env);


    } else {

        do_raise_exception(env, EXCP_RI, GETPC());

    }



    return 0;

}
