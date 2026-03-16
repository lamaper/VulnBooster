static void gen_rfdi(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

     

    gen_helper_rfdi(cpu_env);

    gen_sync_exception(ctx);


}
