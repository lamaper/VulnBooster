static void gen_mfdcrx(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);

        return;

    }

     

    gen_update_nip(ctx, ctx->nip - 4);

    gen_helper_load_dcr(cpu_gpr[rD(ctx->opcode)], cpu_env,

                        cpu_gpr[rA(ctx->opcode)]);


}
