static int mpeg_decode_end ( AVCodecContext * avctx ) {
 Mpeg1Context * s = avctx -> priv_data ;
 if ( s -> mpeg_enc_ctx_allocated ) ff_MPV_common_end ( & s -> mpeg_enc_ctx ) ;
 return 0 ;
 }