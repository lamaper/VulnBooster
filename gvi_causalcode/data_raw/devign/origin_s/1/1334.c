static void put_psr(target_ulong val)

{

    env->psr = val & PSR_ICC;

    env->psref = (val & PSR_EF)? 1 : 0;

    env->psrpil = (val & PSR_PIL) >> 8;


    cpu_check_irqs(env);


    env->psrs = (val & PSR_S)? 1 : 0;

    env->psrps = (val & PSR_PS)? 1 : 0;


    env->psret = (val & PSR_ET)? 1 : 0;


    set_cwp(val & PSR_CWP);

    env->cc_op = CC_OP_FLAGS;

}
