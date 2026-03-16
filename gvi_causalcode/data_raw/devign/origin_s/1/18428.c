static void aio_signal_handler(int signum)

{


    CPUState *env = cpu_single_env;

    if (env) {

         

        cpu_interrupt(env, CPU_INTERRUPT_EXIT);


        if (env->kqemu_enabled) {

            kqemu_cpu_interrupt(env);

        }


    }


}
