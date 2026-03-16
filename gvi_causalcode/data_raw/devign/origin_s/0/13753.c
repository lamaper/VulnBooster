void cpu_breakpoint_remove_by_ref(CPUState *env, CPUBreakpoint *breakpoint)

{


    TAILQ_REMOVE(&env->breakpoints, breakpoint, entry);



    breakpoint_invalidate(env, breakpoint->pc);



    qemu_free(breakpoint);


}
