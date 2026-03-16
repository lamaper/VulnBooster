int cpu_breakpoint_remove(CPUState *env, target_ulong pc, int flags)

{


    CPUBreakpoint *bp;



    TAILQ_FOREACH(bp, &env->breakpoints, entry) {

        if (bp->pc == pc && bp->flags == flags) {

            cpu_breakpoint_remove_by_ref(env, bp);

            return 0;

        }

    }

    return -ENOENT;


    return -ENOSYS;


}
