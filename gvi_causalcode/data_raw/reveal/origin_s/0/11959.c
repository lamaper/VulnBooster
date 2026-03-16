int vp8_denoiser_allocate ( VP8_DENOISER * denoiser , int width , int height , int num_mb_rows , int num_mb_cols , int mode ) {
 int i ;
 assert ( denoiser ) ;
 denoiser -> num_mb_cols = num_mb_cols ;
 for ( i = 0 ;
 i < MAX_REF_FRAMES ;
 i ++ ) {
 denoiser -> yv12_running_avg [ i ] . flags = 0 ;
 if ( vp8_yv12_alloc_frame_buffer ( & ( denoiser -> yv12_running_avg [ i ] ) , width , height , VP8BORDERINPIXELS ) < 0 ) {
 vp8_denoiser_free ( denoiser ) ;
 return 1 ;
 }
 vpx_memset ( denoiser -> yv12_running_avg [ i ] . buffer_alloc , 0 , denoiser -> yv12_running_avg [ i ] . frame_size ) ;
 }
 denoiser -> yv12_mc_running_avg . flags = 0 ;
 if ( vp8_yv12_alloc_frame_buffer ( & ( denoiser -> yv12_mc_running_avg ) , width , height , VP8BORDERINPIXELS ) < 0 ) {
 vp8_denoiser_free ( denoiser ) ;
 return 1 ;
 }
 vpx_memset ( denoiser -> yv12_mc_running_avg . buffer_alloc , 0 , denoiser -> yv12_mc_running_avg . frame_size ) ;
 if ( vp8_yv12_alloc_frame_buffer ( & denoiser -> yv12_last_source , width , height , VP8BORDERINPIXELS ) < 0 ) {
 vp8_denoiser_free ( denoiser ) ;
 return 1 ;
 }
 vpx_memset ( denoiser -> yv12_last_source . buffer_alloc , 0 , denoiser -> yv12_last_source . frame_size ) ;
 denoiser -> denoise_state = vpx_calloc ( ( num_mb_rows * num_mb_cols ) , 1 ) ;
 vpx_memset ( denoiser -> denoise_state , 0 , ( num_mb_rows * num_mb_cols ) ) ;
 vp8_denoiser_set_parameters ( denoiser , mode ) ;
 denoiser -> nmse_source_diff = 0 ;
 denoiser -> nmse_source_diff_count = 0 ;
 denoiser -> qp_avg = 0 ;
 denoiser -> qp_threshold_up = 80 ;
 denoiser -> qp_threshold_down = 128 ;
 denoiser -> bitrate_threshold = 200000 ;
 denoiser -> threshold_aggressive_mode = 35 ;
 if ( width * height > 640 * 480 ) {
 denoiser -> bitrate_threshold = 500000 ;
 denoiser -> threshold_aggressive_mode = 100 ;
 }
 else if ( width * height > 960 * 540 ) {
 denoiser -> bitrate_threshold = 800000 ;
 denoiser -> threshold_aggressive_mode = 150 ;
 }
 else if ( width * height > 1280 * 720 ) {
 denoiser -> bitrate_threshold = 2000000 ;
 denoiser -> threshold_aggressive_mode = 1400 ;
 }
 return 0 ;
 }