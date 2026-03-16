static void gen_rfi(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


     

     

    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

    gen_update_cfar(ctx, ctx->nip);

    gen_helper_rfi(cpu_env);

    gen_sync_exception(ctx);


}
