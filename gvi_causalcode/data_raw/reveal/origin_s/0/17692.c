static VP9_REFFRAME ref_frame_to_vp9_reframe ( vpx_ref_frame_type_t frame ) {
 switch ( frame ) {
 case VP8_LAST_FRAME : return VP9_LAST_FLAG ;
 case VP8_GOLD_FRAME : return VP9_GOLD_FLAG ;
 case VP8_ALTR_FRAME : return VP9_ALT_FLAG ;
 }
 assert ( 0 && "Invalid Reference Frame" ) ;
 return VP9_LAST_FLAG ;
 }