static void gen_msgclr(DisasContext *ctx)

{


    GEN_PRIV;


    CHK_SV;

    gen_helper_msgclr(cpu_env, cpu_gpr[rB(ctx->opcode)]);


}
