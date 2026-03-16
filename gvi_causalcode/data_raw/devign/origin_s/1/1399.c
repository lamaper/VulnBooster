static void do_unassigned_access(target_ulong addr, int is_write, int is_exec,

                          int is_asi, int size)


void do_unassigned_access(target_phys_addr_t addr, int is_write, int is_exec,

                          int is_asi, int size)


{

    CPUState *saved_env;



     

    saved_env = env;

    env = cpu_single_env;


    printf("Unassigned mem access to " TARGET_FMT_plx " from " TARGET_FMT_lx

           "\n", addr, env->pc);




    if (is_exec)

        raise_exception(TT_CODE_ACCESS);

    else

        raise_exception(TT_DATA_ACCESS);



    env = saved_env;

}
