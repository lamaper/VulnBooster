void vp9_denoiser_reset_frame_stats ( PICK_MODE_CONTEXT * ctx ) {
 ctx -> zeromv_sse = UINT_MAX ;
 ctx -> newmv_sse = UINT_MAX ;
 }