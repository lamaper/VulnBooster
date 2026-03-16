static int get_scale_factor ( H264Context * const h , int poc , int poc1 , int i ) {
 int poc0 = h -> ref_list [ 0 ] [ i ] . poc ;
 int td = av_clip ( poc1 - poc0 , - 128 , 127 ) ;
 if ( td == 0 || h -> ref_list [ 0 ] [ i ] . long_ref ) {
 return 256 ;
 }
 else {
 int tb = av_clip ( poc - poc0 , - 128 , 127 ) ;
 int tx = ( 16384 + ( FFABS ( td ) >> 1 ) ) / td ;
 return av_clip ( ( tb * tx + 32 ) >> 6 , - 1024 , 1023 ) ;
 }
 }