static void calc_psnr ( const YV12_BUFFER_CONFIG * a , const YV12_BUFFER_CONFIG * b , PSNR_STATS * psnr ) {
 const int widths [ 3 ] = {
 a -> y_width , a -> uv_width , a -> uv_width }
 ;
 const int heights [ 3 ] = {
 a -> y_height , a -> uv_height , a -> uv_height }
 ;
 const uint8_t * a_planes [ 3 ] = {
 a -> y_buffer , a -> u_buffer , a -> v_buffer }
 ;
 const int a_strides [ 3 ] = {
 a -> y_stride , a -> uv_stride , a -> uv_stride }
 ;
 const uint8_t * b_planes [ 3 ] = {
 b -> y_buffer , b -> u_buffer , b -> v_buffer }
 ;
 const int b_strides [ 3 ] = {
 b -> y_stride , b -> uv_stride , b -> uv_stride }
 ;
 int i ;
 uint64_t total_sse = 0 ;
 uint32_t total_samples = 0 ;
 for ( i = 0 ;
 i < 3 ;
 ++ i ) {
 const int w = widths [ i ] ;
 const int h = heights [ i ] ;
 const uint32_t samples = w * h ;
 const uint64_t sse = get_sse ( a_planes [ i ] , a_strides [ i ] , b_planes [ i ] , b_strides [ i ] , w , h ) ;
 psnr -> sse [ 1 + i ] = sse ;
 psnr -> samples [ 1 + i ] = samples ;
 psnr -> psnr [ 1 + i ] = vpx_sse_to_psnr ( samples , 255.0 , ( double ) sse ) ;
 total_sse += sse ;
 total_samples += samples ;
 }
 psnr -> sse [ 0 ] = total_sse ;
 psnr -> samples [ 0 ] = total_samples ;
 psnr -> psnr [ 0 ] = vpx_sse_to_psnr ( ( double ) total_samples , 255.0 , ( double ) total_sse ) ;
 }