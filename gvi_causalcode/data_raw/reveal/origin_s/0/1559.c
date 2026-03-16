void vp9_remove_compressor ( VP9_COMP * cpi ) {
 unsigned int i ;
 if ( ! cpi ) return ;
 if ( cpi && ( cpi -> common . current_video_frame > 0 ) ) {

 if ( cpi -> oxcf . pass != 1 ) {
 FILE * f = fopen ( "opsnr.stt" , "a" ) ;
 double time_encoded = ( cpi -> last_end_time_stamp_seen - cpi -> first_time_stamp_ever ) / 10000000.000 ;
 double total_encode_time = ( cpi -> time_receive_data + cpi -> time_compress_data ) / 1000.000 ;
 double dr = ( double ) cpi -> bytes * ( double ) 8 / ( double ) 1000 / time_encoded ;
 if ( cpi -> b_calculate_psnr ) {
 const double total_psnr = vpx_sse_to_psnr ( ( double ) cpi -> total_samples , 255.0 , ( double ) cpi -> total_sq_error ) ;
 const double totalp_psnr = vpx_sse_to_psnr ( ( double ) cpi -> totalp_samples , 255.0 , ( double ) cpi -> totalp_sq_error ) ;
 const double total_ssim = 100 * pow ( cpi -> summed_quality / cpi -> summed_weights , 8.0 ) ;
 const double totalp_ssim = 100 * pow ( cpi -> summedp_quality / cpi -> summedp_weights , 8.0 ) ;
 fprintf ( f , "Bitrate\tAVGPsnr\tGLBPsnr\tAVPsnrP\tGLPsnrP\t" "VPXSSIM\tVPSSIMP\t Time(ms)\n" ) ;
 fprintf ( f , "%7.2f\t%7.3f\t%7.3f\t%7.3f\t%7.3f\t%7.3f\t%7.3f\t%8.0f\n" , dr , cpi -> total / cpi -> count , total_psnr , cpi -> totalp / cpi -> count , totalp_psnr , total_ssim , totalp_ssim , total_encode_time ) ;
 }
 if ( cpi -> b_calculate_ssimg ) {
 fprintf ( f , "BitRate\tSSIM_Y\tSSIM_U\tSSIM_V\tSSIM_A\t Time(ms)\n" ) ;
 fprintf ( f , "%7.2f\t%6.4f\t%6.4f\t%6.4f\t%6.4f\t%8.0f\n" , dr , cpi -> total_ssimg_y / cpi -> count , cpi -> total_ssimg_u / cpi -> count , cpi -> total_ssimg_v / cpi -> count , cpi -> total_ssimg_all / cpi -> count , total_encode_time ) ;
 }
 fclose ( f ) ;
 }

 printf ( "\n_pick_loop_filter_level:%d\n" , cpi -> time_pick_lpf / 1000 ) ;
 printf ( "\n_frames recive_data encod_mb_row compress_frame Total\n" ) ;
 printf ( "%6d %10ld %10ld %10ld %10ld\n" , cpi -> common . current_video_frame , cpi -> time_receive_data / 1000 , cpi -> time_encode_sb_row / 1000 , cpi -> time_compress_data / 1000 , ( cpi -> time_receive_data + cpi -> time_compress_data ) / 1000 ) ;
 }


 vp9_denoiser_free ( & ( cpi -> denoiser ) ) ;
 }

 vpx_free ( cpi -> tok ) ;
 for ( i = 0 ;
 i < sizeof ( cpi -> mbgraph_stats ) / sizeof ( cpi -> mbgraph_stats [ 0 ] ) ;
 ++ i ) {
 vpx_free ( cpi -> mbgraph_stats [ i ] . mb_stats ) ;
 }

 vpx_free ( cpi -> twopass . frame_mb_stats_buf ) ;
 cpi -> twopass . frame_mb_stats_buf = NULL ;
 }

 vpx_free ( cpi ) ;



 if ( framepsnr ) fclose ( framepsnr ) ;
 if ( kf_list ) fclose ( kf_list ) ;
