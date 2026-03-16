void vp9_denoiser_update_frame_info ( VP9_DENOISER * denoiser , YV12_BUFFER_CONFIG src , FRAME_TYPE frame_type , int refresh_alt_ref_frame , int refresh_golden_frame , int refresh_last_frame ) {
 if ( frame_type == KEY_FRAME ) {
 int i ;
 for ( i = 1 ;
 i < MAX_REF_FRAMES ;
 ++ i ) {
 copy_frame ( denoiser -> running_avg_y [ i ] , src ) ;
 }
 }
 else {
 if ( refresh_alt_ref_frame ) {
 copy_frame ( denoiser -> running_avg_y [ ALTREF_FRAME ] , denoiser -> running_avg_y [ INTRA_FRAME ] ) ;
 }
 if ( refresh_golden_frame ) {
 copy_frame ( denoiser -> running_avg_y [ GOLDEN_FRAME ] , denoiser -> running_avg_y [ INTRA_FRAME ] ) ;
 }
 if ( refresh_last_frame ) {
 copy_frame ( denoiser -> running_avg_y [ LAST_FRAME ] , denoiser -> running_avg_y [ INTRA_FRAME ] ) ;
 }
 }
 }