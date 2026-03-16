static void exception_action(CPUState *cpu)

{


    X86CPU *x86_cpu = X86_CPU(cpu);

    CPUX86State *env1 = &x86_cpu->env;



    raise_exception_err(env1, cpu->exception_index, env1->error_code);


    cpu_loop_exit(cpu);


}
