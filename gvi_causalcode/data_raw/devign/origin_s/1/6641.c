void helper_single_step(CPUX86State *env)

{


    check_hw_breakpoints(env, 1);

    env->dr[6] |= DR6_BS;


    raise_exception(env, EXCP01_DB);

}
