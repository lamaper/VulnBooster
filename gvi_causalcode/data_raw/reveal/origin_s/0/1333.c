static void cavs_flush ( AVCodecContext * avctx ) {
 AVSContext * h = avctx -> priv_data ;
 h -> got_keyframe = 0 ;
 }