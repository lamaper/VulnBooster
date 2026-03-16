static void flip ( AVCodecContext * avctx , AVPicture * picture ) {
 picture -> data [ 0 ] += picture -> linesize [ 0 ] * ( avctx -> height - 1 ) ;
 picture -> linesize [ 0 ] *= - 1 ;
 }