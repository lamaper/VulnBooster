void do_icbi (void)

{

    uint32_t tmp;


    if (!msr_sf)

        T0 &= 0xFFFFFFFFULL;


    tmp = ldl_kernel(T0);

    T0 &= ~(ICACHE_LINE_SIZE - 1);

    tb_invalidate_page_range(T0, T0 + ICACHE_LINE_SIZE);

}
