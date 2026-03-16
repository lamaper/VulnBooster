static void gen_slbmte(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);

        return;

    }

    gen_helper_store_slb(cpu_env, cpu_gpr[rB(ctx->opcode)],

                         cpu_gpr[rS(ctx->opcode)]);


}
