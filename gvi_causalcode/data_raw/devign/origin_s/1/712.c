static void gen_rfci(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

     

    gen_helper_rfci(cpu_env);

    gen_sync_exception(ctx);


}
