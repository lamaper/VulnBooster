void do_POWER_rac (void)

{


    mmu_ctx_t ctx;



     

    if (get_physical_address(env, &ctx, T0, 0, ACCESS_INT, 1) == 0)

        T0 = ctx.raddr;


}
