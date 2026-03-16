static void gen_rfid(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


     

    if (unlikely(!ctx->mem_idx)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }


    gen_helper_rfid();

    gen_sync_exception(ctx);


}