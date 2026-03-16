void qemu_cpu_kick_self(void)

{


    assert(cpu_single_env);



    raise(SIG_IPI);


    abort();


}
