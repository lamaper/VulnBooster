void helper_wrpil(CPUSPARCState *env, target_ulong new_pil)

{


    trace_win_helper_wrpil(env->psrpil, (uint32_t)new_pil);



    env->psrpil = new_pil;



    if (cpu_interrupts_enabled(env)) {


        cpu_check_irqs(env);


    }


}