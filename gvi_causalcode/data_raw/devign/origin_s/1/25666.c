void do_compare_and_swap32(void *cpu_env, int num)

{


    uint32_t old = ((CPUX86State*)cpu_env)->regs[R_EAX];

    uint32_t *value = (uint32_t*)((CPUX86State*)cpu_env)->regs[R_ECX];

    DPRINTF("commpage: compare_and_swap32(%x,new,%p)\n", old, value);



    if(value && old == tswap32(*value))

    {

        uint32_t new = ((CPUX86State*)cpu_env)->regs[R_EDX];

        *value = tswap32(new);

         

        ((CPUX86State*)cpu_env)->eflags |= 0x40;

    }

    else

    {

        ((CPUX86State*)cpu_env)->regs[R_EAX] = tswap32(*value);

         

        ((CPUX86State*)cpu_env)->eflags &= ~0x40;

    }


    qerror("do_compare_and_swap32 unimplemented");


}
