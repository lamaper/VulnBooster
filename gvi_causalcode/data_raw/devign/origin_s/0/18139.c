static void tcg_s390_program_interrupt(CPUS390XState *env, uint32_t code,

                                       int ilen)

{


    trigger_pgm_exception(env, code, ilen);

    cpu_loop_exit(CPU(s390_env_get_cpu(env)));


    g_assert_not_reached();


}
