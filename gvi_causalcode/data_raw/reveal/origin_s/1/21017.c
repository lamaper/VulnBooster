const char * vpx_svc_dump_statistics ( SvcContext * svc_ctx ) {
 int number_of_frames , encode_frame_count ;
 int i , j ;
 uint32_t bytes_total = 0 ;
 double scale [ COMPONENTS ] ;
 double psnr [ COMPONENTS ] ;
 double mse [ COMPONENTS ] ;
 double y_scale ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || si == NULL ) return NULL ;
 svc_log_reset ( svc_ctx ) ;
 encode_frame_count = si -> encode_frame_count ;
 if ( si -> encode_frame_count <= 0 ) return vpx_svc_get_message ( svc_ctx ) ;
 svc_log ( svc_ctx , SVC_LOG_INFO , "\n" ) ;
 for ( i = 0 ;
 i < si -> layers ;
 ++ i ) {
 number_of_frames = encode_frame_count ;
 svc_log ( svc_ctx , SVC_LOG_INFO , "Layer %d Average PSNR=[%2.3f, %2.3f, %2.3f, %2.3f], Bytes=[%u]\n" , i , ( double ) si -> psnr_sum [ i ] [ 0 ] / number_of_frames , ( double ) si -> psnr_sum [ i ] [ 1 ] / number_of_frames , ( double ) si -> psnr_sum [ i ] [ 2 ] / number_of_frames , ( double ) si -> psnr_sum [ i ] [ 3 ] / number_of_frames , si -> bytes_sum [ i ] ) ;
 y_scale = si -> width * si -> height * 255.0 * 255.0 * number_of_frames ;
 scale [ 1 ] = y_scale ;
 scale [ 2 ] = scale [ 3 ] = y_scale / 4 ;
 scale [ 0 ] = y_scale * 1.5 ;
 for ( j = 0 ;
 j < COMPONENTS ;
 j ++ ) {
 psnr [ j ] = calc_psnr ( si -> sse_sum [ i ] [ j ] / scale [ j ] ) ;
 mse [ j ] = si -> sse_sum [ i ] [ j ] * 255.0 * 255.0 / scale [ j ] ;
 }
 svc_log ( svc_ctx , SVC_LOG_INFO , "Layer %d Overall PSNR=[%2.3f, %2.3f, %2.3f, %2.3f]\n" , i , psnr [ 0 ] , psnr [ 1 ] , psnr [ 2 ] , psnr [ 3 ] ) ;
 svc_log ( svc_ctx , SVC_LOG_INFO , "Layer %d Overall MSE=[%2.3f, %2.3f, %2.3f, %2.3f]\n" , i , mse [ 0 ] , mse [ 1 ] , mse [ 2 ] , mse [ 3 ] ) ;
 bytes_total += si -> bytes_sum [ i ] ;
 si -> bytes_sum [ i ] = 0 ;
 for ( j = 0 ;
 j < COMPONENTS ;
 ++ j ) {
 si -> psnr_sum [ i ] [ j ] = 0 ;
 si -> sse_sum [ i ] [ j ] = 0 ;
 }
 }
 si -> encode_frame_count = 0 ;
 svc_log ( svc_ctx , SVC_LOG_INFO , "Total Bytes=[%u]\n" , bytes_total ) ;
 return vpx_svc_get_message ( svc_ctx ) ;
 }