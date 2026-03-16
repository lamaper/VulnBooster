static void uc32_cpu_initfn(Object *obj)

{

    CPUState *cs = CPU(obj);

    UniCore32CPU *cpu = UNICORE32_CPU(obj);

    CPUUniCore32State *env = &cpu->env;

    static bool inited;



    cs->env_ptr = env;

    cpu_exec_init(cs, &error_abort);


    env->uncached_asr = ASR_MODE_USER;

    env->regs[31] = 0;


    env->uncached_asr = ASR_MODE_PRIV;

    env->regs[31] = 0x03000000;




    tlb_flush(cs, 1);



    if (tcg_enabled() && !inited) {

        inited = true;

        uc32_translate_init();

    }

}
