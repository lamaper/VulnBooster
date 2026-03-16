static double calc_psnr ( double d ) {
 if ( d == 0 ) return 100 ;
 return - 10.0 * log ( d ) / log ( 10.0 ) ;
 }