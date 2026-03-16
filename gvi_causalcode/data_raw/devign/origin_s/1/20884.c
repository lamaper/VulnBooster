static void unassigned_mem_writew(void *opaque, target_phys_addr_t addr, uint32_t val)

{


    printf("Unassigned mem write " TARGET_FMT_plx " = 0x%x\n", addr, val);



    do_unassigned_access(addr, 1, 0, 0, 2);


}
