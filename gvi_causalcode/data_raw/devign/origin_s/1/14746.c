static void gen_mtdcr(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);


    TCGv dcrn;

    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);

        return;

    }

     

    gen_update_nip(ctx, ctx->nip - 4);

    dcrn = tcg_const_tl(SPR(ctx->opcode));

    gen_helper_store_dcr(cpu_env, dcrn, cpu_gpr[rS(ctx->opcode)]);

    tcg_temp_free(dcrn);


}
