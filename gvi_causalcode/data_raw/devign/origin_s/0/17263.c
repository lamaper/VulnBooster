CPUX86State *cpu_x86_init(const char *cpu_model)

{

    CPUX86State *env;

    static int inited;



    env = qemu_mallocz(sizeof(CPUX86State));

    cpu_exec_init(env);

    env->cpu_model_str = cpu_model;



     

    if (!inited) {

        inited = 1;

        optimize_flags_init();


        prev_debug_excp_handler =

            cpu_set_debug_excp_handler(breakpoint_handler);


    }

    if (cpu_x86_register(env, cpu_model) < 0) {

        cpu_x86_close(env);

        return NULL;

    }

    mce_init(env);

    cpu_reset(env);


    kqemu_init(env);




    qemu_init_vcpu(env);



    return env;

}
