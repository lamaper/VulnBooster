static void mpc7_decode_flush ( AVCodecContext * avctx ) {
 MPCContext * c = avctx -> priv_data ;
 memset ( c -> oldDSCF , 0 , sizeof ( c -> oldDSCF ) ) ;
 c -> frames_to_skip = 32 ;
 }