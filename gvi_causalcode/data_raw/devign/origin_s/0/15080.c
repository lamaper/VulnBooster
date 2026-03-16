static void gdb_breakpoint_remove_all(CPUState *env)

{

    cpu_breakpoint_remove_all(env, BP_GDB);


    cpu_watchpoint_remove_all(env, BP_GDB);


}
