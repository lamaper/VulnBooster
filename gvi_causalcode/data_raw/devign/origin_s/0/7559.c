static void unassigned_mem_write(void *opaque, target_phys_addr_t addr,

                                 uint64_t val, unsigned size)

{


    printf("Unassigned mem write " TARGET_FMT_plx " = 0x%"PRIx64"\n", addr, val);



    cpu_unassigned_access(cpu_single_env, addr, 1, 0, 0, size);


}
