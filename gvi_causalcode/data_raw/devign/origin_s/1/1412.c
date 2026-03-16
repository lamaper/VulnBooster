static void gen_slbmfev(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);

        return;

    }

    gen_helper_load_slb_vsid(cpu_gpr[rS(ctx->opcode)], cpu_env,

                             cpu_gpr[rB(ctx->opcode)]);


}
