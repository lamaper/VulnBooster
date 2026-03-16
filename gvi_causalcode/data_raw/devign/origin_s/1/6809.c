static void gen_dcread(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


    TCGv EA, val;

    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

    gen_set_access_type(ctx, ACCESS_CACHE);

    EA = tcg_temp_new();

    gen_addr_reg_index(ctx, EA);

    val = tcg_temp_new();

    gen_qemu_ld32u(ctx, val, EA);

    tcg_temp_free(val);

    tcg_gen_mov_tl(cpu_gpr[rD(ctx->opcode)], EA);

    tcg_temp_free(EA);


}
