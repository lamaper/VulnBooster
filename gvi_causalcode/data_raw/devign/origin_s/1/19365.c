void ff_float_init_arm_vfp(DSPContext* c, AVCodecContext *avctx)


{


    c->vector_fmul = vector_fmul_vfp;


    c->vector_fmul_reverse = vector_fmul_reverse_vfp;



    c->float_to_int16 = float_to_int16_vfp;



}

