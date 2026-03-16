static void flush ( AVCodecContext * avctx ) {
 WMAProDecodeCtx * s = avctx -> priv_data ;
 int i ;
 for ( i = 0 ;
 i < avctx -> channels ;
 i ++ ) memset ( s -> channel [ i ] . out , 0 , s -> samples_per_frame * sizeof ( * s -> channel [ i ] . out ) ) ;
 s -> packet_loss = 1 ;
 }