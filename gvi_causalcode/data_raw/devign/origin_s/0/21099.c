static void unassigned_mem_write(void *opaque, hwaddr addr,

                                 uint64_t val, unsigned size)

{


    printf("Unassigned mem write " TARGET_FMT_plx " = 0x%"PRIx64"\n", addr, val);



    cpu_unassigned_access(cpu_single_env, addr, 1, 0, 0, size);


}
