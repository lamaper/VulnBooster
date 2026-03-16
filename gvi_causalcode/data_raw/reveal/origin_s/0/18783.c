static void prepare_avpic ( MimicContext * ctx , AVPicture * dst , AVFrame * src ) {
 int i ;
 dst -> data [ 0 ] = src -> data [ 0 ] + ( ctx -> avctx -> height - 1 ) * src -> linesize [ 0 ] ;
 dst -> data [ 1 ] = src -> data [ 2 ] + ( ( ctx -> avctx -> height >> 1 ) - 1 ) * src -> linesize [ 2 ] ;
 dst -> data [ 2 ] = src -> data [ 1 ] + ( ( ctx -> avctx -> height >> 1 ) - 1 ) * src -> linesize [ 1 ] ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) dst -> linesize [ i ] = - src -> linesize [ i ] ;
 }