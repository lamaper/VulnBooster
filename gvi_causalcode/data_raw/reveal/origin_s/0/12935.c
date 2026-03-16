static void show_psnr ( struct stream_state * stream ) {
 int i ;
 double ovpsnr ;
 if ( ! stream -> psnr_count ) return ;
 fprintf ( stderr , "Stream %d PSNR (Overall/Avg/Y/U/V)" , stream -> index ) ;
 ovpsnr = sse_to_psnr ( ( double ) stream -> psnr_samples_total , 255.0 , ( double ) stream -> psnr_sse_total ) ;
 fprintf ( stderr , " %.3f" , ovpsnr ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 fprintf ( stderr , " %.3f" , stream -> psnr_totals [ i ] / stream -> psnr_count ) ;
 }
 fprintf ( stderr , "\n" ) ;
 }