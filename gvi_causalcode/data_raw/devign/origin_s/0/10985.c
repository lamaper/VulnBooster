static uint64_t unassigned_mem_read(void *opaque, target_phys_addr_t addr,

                                    unsigned size)

{


    printf("Unassigned mem read " TARGET_FMT_plx "\n", addr);



    cpu_unassigned_access(cpu_single_env, addr, 0, 0, 0, size);


    return 0;

}
