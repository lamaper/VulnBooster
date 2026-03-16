void vp9_denoiser_update_frame_stats ( MB_MODE_INFO * mbmi , unsigned int sse , PREDICTION_MODE mode , PICK_MODE_CONTEXT * ctx ) {
 if ( mbmi -> mv [ 0 ] . as_int == 0 && sse < ctx -> zeromv_sse ) {
 ctx -> zeromv_sse = sse ;
 ctx -> best_zeromv_reference_frame = mbmi -> ref_frame [ 0 ] ;
 }
 if ( mode == NEWMV ) {
 ctx -> newmv_sse = sse ;
 ctx -> best_sse_inter_mode = mode ;
 ctx -> best_sse_mv = mbmi -> mv [ 0 ] ;
 ctx -> best_reference_frame = mbmi -> ref_frame [ 0 ] ;
 }
 }