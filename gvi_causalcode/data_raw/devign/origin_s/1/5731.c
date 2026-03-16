void ff_mlp_init_x86(DSPContext* c, AVCodecContext *avctx)

{


    c->mlp_filter_channel = mlp_filter_channel_x86;


}
