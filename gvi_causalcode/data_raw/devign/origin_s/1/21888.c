static void gen_tlbsync(DisasContext *ctx)

{


    GEN_PRIV;


    CHK_HV;



     

    gen_check_tlb_flush(ctx);


}
