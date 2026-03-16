void vp8_denoiser_free ( VP8_DENOISER * denoiser ) {
 int i ;
 assert ( denoiser ) ;
 for ( i = 0 ;
 i < MAX_REF_FRAMES ;
 i ++ ) {
 vp8_yv12_de_alloc_frame_buffer ( & denoiser -> yv12_running_avg [ i ] ) ;
 }
 vp8_yv12_de_alloc_frame_buffer ( & denoiser -> yv12_mc_running_avg ) ;
 vp8_yv12_de_alloc_frame_buffer ( & denoiser -> yv12_last_source ) ;
 vpx_free ( denoiser -> denoise_state ) ;
 }