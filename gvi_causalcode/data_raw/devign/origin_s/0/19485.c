static int gdb_breakpoint_remove(CPUState *env, target_ulong addr,

                                 target_ulong len, int type)

{

    switch (type) {

    case GDB_BREAKPOINT_SW:

    case GDB_BREAKPOINT_HW:

        return cpu_breakpoint_remove(env, addr, BP_GDB);


    case GDB_WATCHPOINT_WRITE:

    case GDB_WATCHPOINT_READ:

    case GDB_WATCHPOINT_ACCESS:

        return cpu_watchpoint_remove(env, addr, len, xlat_gdb_type[type]);


    default:

        return -ENOSYS;

    }

}
