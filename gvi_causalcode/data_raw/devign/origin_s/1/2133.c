static inline int cpu_gdb_index(CPUState *cpu)

{


    return cpu->host_tid;


    return cpu->cpu_index + 1;


}
