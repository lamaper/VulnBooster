CPUPPCState *cpu_ppc_init(void)

{

    CPUPPCState *env;



    cpu_exec_init();



    env = qemu_mallocz(sizeof(CPUPPCState));

    if (!env)

        return NULL;


    setup_machine(env, 0);


 

    env->spr[PVR] = 0x00080100;  


    tlb_flush(env, 1);


     

    msr_se = 1;


    msr_fp = 1;  

    msr_me = 1;  


    msr_pr = 1;

    cpu_ppc_register(env, 0x00080000);


    env->nip = 0xFFFFFFFC;


    env->access_type = ACCESS_INT;

    cpu_single_env = env;

    return env;

}
