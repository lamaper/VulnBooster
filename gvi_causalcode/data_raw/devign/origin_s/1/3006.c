void cpu_reset(CPUM68KState *env)
{
    memset(env, 0, offsetof(CPUM68KState, breakpoints));

    env->sr = 0x2700;

    m68k_switch_sp(env);
     
    env->cc_op = CC_OP_FLAGS;
     
    env->pc = 0;
    tlb_flush(env, 1);