static void gen_rfmci(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

     

    gen_helper_rfmci(cpu_env);

    gen_sync_exception(ctx);


}
