static void gen_wrteei(DisasContext *ctx)

{


    gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);


    if (unlikely(ctx->pr)) {

        gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);

        return;

    }

    if (ctx->opcode & 0x00008000) {

        tcg_gen_ori_tl(cpu_msr, cpu_msr, (1 << MSR_EE));

         

        gen_stop_exception(ctx);

    } else {

        tcg_gen_andi_tl(cpu_msr, cpu_msr, ~(1 << MSR_EE));

    }


}
