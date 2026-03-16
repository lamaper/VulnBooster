static void gen_tlbli_74xx(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

    gen_helper_74xx_tlbi(cpu_env, cpu_gpr[rB(ctx->opcode)]);


}
