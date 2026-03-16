static uint64_t unassigned_mem_read(void *opaque, hwaddr addr,

                                    unsigned size)

{


    printf("Unassigned mem read " TARGET_FMT_plx "\n", addr);


    if (current_cpu != NULL) {

        cpu_unassigned_access(current_cpu, addr, false, false, 0, size);

    }

    return -1ULL;

}
