void vp9_denoiser_denoise ( VP9_DENOISER * denoiser , MACROBLOCK * mb , int mi_row , int mi_col , BLOCK_SIZE bs , PICK_MODE_CONTEXT * ctx ) {
 int motion_magnitude = 0 ;
 VP9_DENOISER_DECISION decision = FILTER_BLOCK ;
 YV12_BUFFER_CONFIG avg = denoiser -> running_avg_y [ INTRA_FRAME ] ;
 YV12_BUFFER_CONFIG mc_avg = denoiser -> mc_running_avg_y ;
 uint8_t * avg_start = block_start ( avg . y_buffer , avg . y_stride , mi_row , mi_col ) ;
 uint8_t * mc_avg_start = block_start ( mc_avg . y_buffer , mc_avg . y_stride , mi_row , mi_col ) ;
 struct buf_2d src = mb -> plane [ 0 ] . src ;
 decision = perform_motion_compensation ( denoiser , mb , bs , denoiser -> increase_denoising , mi_row , mi_col , ctx , & motion_magnitude ) ;
 if ( decision == FILTER_BLOCK ) {
 decision = denoiser_filter ( src . buf , src . stride , mc_avg_start , mc_avg . y_stride , avg_start , avg . y_stride , 0 , bs , motion_magnitude ) ;
 }
 if ( decision == FILTER_BLOCK ) {
 copy_block ( src . buf , src . stride , avg_start , avg . y_stride , bs ) ;
 }
 else {
 copy_block ( avg_start , avg . y_stride , src . buf , src . stride , bs ) ;
 }
 }