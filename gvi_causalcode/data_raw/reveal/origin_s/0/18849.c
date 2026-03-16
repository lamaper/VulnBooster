void vp9_denoiser_free ( VP9_DENOISER * denoiser ) {
 int i ;
 if ( denoiser == NULL ) {
 return ;
 }
 for ( i = 0 ;
 i < MAX_REF_FRAMES ;
 ++ i ) {
 if ( & denoiser -> running_avg_y [ i ] != NULL ) {
 vp9_free_frame_buffer ( & denoiser -> running_avg_y [ i ] ) ;
 }
 }
 if ( & denoiser -> mc_running_avg_y != NULL ) {
 vp9_free_frame_buffer ( & denoiser -> mc_running_avg_y ) ;
 }
 }