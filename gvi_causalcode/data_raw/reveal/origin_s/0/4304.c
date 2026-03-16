static int get_mode ( AVCodecContext * avctx ) {
 if ( avctx -> block_align == 38 ) return 20 ;
 else if ( avctx -> block_align == 50 ) return 30 ;
 else if ( avctx -> bit_rate > 0 ) return avctx -> bit_rate <= 14000 ? 30 : 20 ;
 else return - 1 ;
 }