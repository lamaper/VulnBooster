void vp8_remove_compressor ( VP8_COMP * * ptr ) {
 VP8_COMP * cpi = * ptr ;
 if ( ! cpi ) return ;
 if ( cpi && ( cpi -> common . current_video_frame > 0 ) ) {

 vp8_end_second_pass ( cpi ) ;
 }

 print_tree_update_probs ( ) ;
 print_mode_context ( ) ;

 FILE * f = fopen ( "opsnr.stt" , "a" ) ;
 double time_encoded = ( cpi -> last_end_time_stamp_seen - cpi -> first_time_stamp_ever ) / 10000000.000 ;
 double total_encode_time = ( cpi -> time_receive_data + cpi -> time_compress_data ) / 1000.000 ;
 double dr = ( double ) cpi -> bytes * 8.0 / 1000.0 / time_encoded ;
 if ( cpi -> b_calculate_psnr ) {
 YV12_BUFFER_CONFIG * lst_yv12 = & cpi -> common . yv12_fb [ cpi -> common . lst_fb_idx ] ;
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 int i ;
 fprintf ( f , "Layer\tBitrate\tAVGPsnr\tGLBPsnr\tAVPsnrP\t" "GLPsnrP\tVPXSSIM\t\n" ) ;
 for ( i = 0 ;
 i < ( int ) cpi -> oxcf . number_of_layers ;
 i ++ ) {
 double dr = ( double ) cpi -> bytes_in_layer [ i ] * 8.0 / 1000.0 / time_encoded ;
 double samples = 3.0 / 2 * cpi -> frames_in_layer [ i ] * lst_yv12 -> y_width * lst_yv12 -> y_height ;
 double total_psnr = vpx_sse_to_psnr ( samples , 255.0 , cpi -> total_error2 [ i ] ) ;
 double total_psnr2 = vpx_sse_to_psnr ( samples , 255.0 , cpi -> total_error2_p [ i ] ) ;
 double total_ssim = 100 * pow ( cpi -> sum_ssim [ i ] / cpi -> sum_weights [ i ] , 8.0 ) ;
 fprintf ( f , "%5d\t%7.3f\t%7.3f\t%7.3f\t%7.3f\t" "%7.3f\t%7.3f\n" , i , dr , cpi -> sum_psnr [ i ] / cpi -> frames_in_layer [ i ] , total_psnr , cpi -> sum_psnr_p [ i ] / cpi -> frames_in_layer [ i ] , total_psnr2 , total_ssim ) ;
 }
 }
 else {
 double samples = 3.0 / 2 * cpi -> count * lst_yv12 -> y_width * lst_yv12 -> y_height ;
 double total_psnr = vpx_sse_to_psnr ( samples , 255.0 , cpi -> total_sq_error ) ;
 double total_psnr2 = vpx_sse_to_psnr ( samples , 255.0 , cpi -> total_sq_error2 ) ;
 double total_ssim = 100 * pow ( cpi -> summed_quality / cpi -> summed_weights , 8.0 ) ;
 fprintf ( f , "Bitrate\tAVGPsnr\tGLBPsnr\tAVPsnrP\t" "GLPsnrP\tVPXSSIM\t Time(us)\n" ) ;
 fprintf ( f , "%7.3f\t%7.3f\t%7.3f\t%7.3f\t%7.3f\t" "%7.3f\t%8.0f\n" , dr , cpi -> total / cpi -> count , total_psnr , cpi -> totalp / cpi -> count , total_psnr2 , total_ssim , total_encode_time ) ;
 }
 }
 if ( cpi -> b_calculate_ssimg ) {
 if ( cpi -> oxcf . number_of_layers > 1 ) {
 int i ;
 fprintf ( f , "Layer\tBitRate\tSSIM_Y\tSSIM_U\tSSIM_V\tSSIM_A\t" "Time(us)\n" ) ;
 for ( i = 0 ;
 i < ( int ) cpi -> oxcf . number_of_layers ;
 i ++ ) {
 double dr = ( double ) cpi -> bytes_in_layer [ i ] * 8.0 / 1000.0 / time_encoded ;
 fprintf ( f , "%5d\t%7.3f\t%6.4f\t" "%6.4f\t%6.4f\t%6.4f\t%8.0f\n" , i , dr , cpi -> total_ssimg_y_in_layer [ i ] / cpi -> frames_in_layer [ i ] , cpi -> total_ssimg_u_in_layer [ i ] / cpi -> frames_in_layer [ i ] , cpi -> total_ssimg_v_in_layer [ i ] / cpi -> frames_in_layer [ i ] , cpi -> total_ssimg_all_in_layer [ i ] / cpi -> frames_in_layer [ i ] , total_encode_time ) ;
 }
 }
 else {
 fprintf ( f , "BitRate\tSSIM_Y\tSSIM_U\tSSIM_V\tSSIM_A\t" "Time(us)\n" ) ;
 fprintf ( f , "%7.3f\t%6.4f\t%6.4f\t%6.4f\t%6.4f\t%8.0f\n" , dr , cpi -> total_ssimg_y / cpi -> count , cpi -> total_ssimg_u / cpi -> count , cpi -> total_ssimg_v / cpi -> count , cpi -> total_ssimg_all / cpi -> count , total_encode_time ) ;
 }
 }
 fclose ( f ) ;

 fprintf ( f , "minq:%d -maxq:%d skiptrue:skipfalse = %d:%d\n" , cpi -> oxcf . best_allowed_q , cpi -> oxcf . worst_allowed_q , skiptruecount , skipfalsecount ) ;
 fclose ( f ) ;


 int i ;
 FILE * f = fopen ( "cxspeed.stt" , "a" ) ;
 cnt_pm /= cpi -> common . MBs ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) fprintf ( f , "%5d" , frames_at_speed [ i ] ) ;
 fprintf ( f , "\n" ) ;
 fclose ( f ) ;
 }

 extern int count_mb_seg [ 4 ] ;
 FILE * f = fopen ( "modes.stt" , "a" ) ;
 double dr = ( double ) cpi -> framerate * ( double ) bytes * ( double ) 8 / ( double ) count / ( double ) 1000 ;
 fprintf ( f , "intra_mode in Intra Frames:\n" ) ;
 fprintf ( f , "Y: %8d, %8d, %8d, %8d, %8d\n" , y_modes [ 0 ] , y_modes [ 1 ] , y_modes [ 2 ] , y_modes [ 3 ] , y_modes [ 4 ] ) ;
 fprintf ( f , "UV:%8d, %8d, %8d, %8d\n" , uv_modes [ 0 ] , uv_modes [ 1 ] , uv_modes [ 2 ] , uv_modes [ 3 ] ) ;
 fprintf ( f , "B: " ) ;
 {
 int i ;
 for ( i = 0 ;
 i < 10 ;
 i ++ ) fprintf ( f , "%8d, " , b_modes [ i ] ) ;
 fprintf ( f , "\n" ) ;
 }
 fprintf ( f , "Modes in Inter Frames:\n" ) ;
 fprintf ( f , "Y: %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d, %8d\n" , inter_y_modes [ 0 ] , inter_y_modes [ 1 ] , inter_y_modes [ 2 ] , inter_y_modes [ 3 ] , inter_y_modes [ 4 ] , inter_y_modes [ 5 ] , inter_y_modes [ 6 ] , inter_y_modes [ 7 ] , inter_y_modes [ 8 ] , inter_y_modes [ 9 ] ) ;
 fprintf ( f , "UV:%8d, %8d, %8d, %8d\n" , inter_uv_modes [ 0 ] , inter_uv_modes [ 1 ] , inter_uv_modes [ 2 ] , inter_uv_modes [ 3 ] ) ;
 fprintf ( f , "B: " ) ;
 {
 int i ;
 for ( i = 0 ;
 i < 15 ;
 i ++ ) fprintf ( f , "%8d, " , inter_b_modes [ i ] ) ;
 fprintf ( f , "\n" ) ;
 }
 fprintf ( f , "P:%8d, %8d, %8d, %8d\n" , count_mb_seg [ 0 ] , count_mb_seg [ 1 ] , count_mb_seg [ 2 ] , count_mb_seg [ 3 ] ) ;
 fprintf ( f , "PB:%8d, %8d, %8d, %8d\n" , inter_b_modes [ LEFT4X4 ] , inter_b_modes [ ABOVE4X4 ] , inter_b_modes [ ZERO4X4 ] , inter_b_modes [ NEW4X4 ] ) ;
 fclose ( f ) ;
 }

 int i , j , k ;
 FILE * fmode = fopen ( "modecontext.c" , "w" ) ;
 fprintf ( fmode , "\n#include \"entropymode.h\"\n\n" ) ;
 fprintf ( fmode , "const unsigned int vp8_kf_default_bmode_counts " ) ;
 fprintf ( fmode , "[VP8_BINTRAMODES] [VP8_BINTRAMODES] [VP8_BINTRAMODES] =\n{
\n" ) ;
 for ( i = 0 ;
 i < 10 ;
 i ++ ) {
 fprintf ( fmode , " {
 /* Above Mode : %d */\n" , i ) ;
 for ( j = 0 ;
 j < 10 ;
 j ++ ) {
 fprintf ( fmode , " {
" ) ;
 for ( k = 0 ;
 k < 10 ;
 k ++ ) {
 if ( ! intra_mode_stats [ i ] [ j ] [ k ] ) fprintf ( fmode , " %5d, " , 1 ) ;
 else fprintf ( fmode , " %5d, " , intra_mode_stats [ i ] [ j ] [ k ] ) ;
 }
 fprintf ( fmode , "}
, /* left_mode %d */\n" , j ) ;
 }
 fprintf ( fmode , " }
,\n" ) ;
 }
 fprintf ( fmode , "}
;
\n" ) ;
 fclose ( fmode ) ;
 }

 int i ;
 FILE * f = fopen ( "tokenbits.stt" , "a" ) ;
 for ( i = 0 ;
 i < 28 ;
 i ++ ) fprintf ( f , "%8d" , ( int ) ( Sectionbits [ i ] / 256 ) ) ;
 fprintf ( f , "\n" ) ;
 fclose ( f ) ;
 }

 printf ( "\n_pick_loop_filter_level:%d\n" , cpi -> time_pick_lpf / 1000 ) ;
 printf ( "\n_frames recive_data encod_mb_row compress_frame Total\n" ) ;
 printf ( "%6d %10ld %10ld %10ld %10ld\n" , cpi -> common . current_video_frame , cpi -> time_receive_data / 1000 , cpi -> time_encode_mb_row / 1000 , cpi -> time_compress_data / 1000 , ( cpi -> time_receive_data + cpi -> time_compress_data ) / 1000 ) ;
 }




 vpx_free ( cpi -> mb . ss ) ;
 vpx_free ( cpi -> tok ) ;
 vpx_free ( cpi -> cyclic_refresh_map ) ;
 vpx_free ( cpi -> consec_zero_last ) ;
 vp8_remove_common ( & cpi -> common ) ;
 vpx_free ( cpi ) ;
 * ptr = 0 ;



 if ( framepsnr ) fclose ( framepsnr ) ;
 if ( kf_list ) fclose ( kf_list ) ;
