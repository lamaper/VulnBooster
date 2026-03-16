static uint32_t unassigned_mem_readw(void *opaque, target_phys_addr_t addr)

{


    printf("Unassigned mem read " TARGET_FMT_plx "\n", addr);



    do_unassigned_access(addr, 0, 0, 0, 2);


    return 0;

}
