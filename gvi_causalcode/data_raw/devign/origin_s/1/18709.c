static void openrisc_cpu_initfn(Object *obj)

{

    CPUState *cs = CPU(obj);

    OpenRISCCPU *cpu = OPENRISC_CPU(obj);

    static int inited;



    cs->env_ptr = &cpu->env;

    cpu_exec_init(cs, &error_abort);


    cpu_openrisc_mmu_init(cpu);




    if (tcg_enabled() && !inited) {

        inited = 1;

        openrisc_translate_init();

    }

}
