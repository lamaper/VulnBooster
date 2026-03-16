void vp8_mbpost_proc_across_ip_c ( unsigned char * src , int pitch , int rows , int cols , int flimit ) {
 int r , c , i ;
 unsigned char * s = src ;
 unsigned char d [ 16 ] ;
 for ( r = 0 ;
 r < rows ;
 r ++ ) {
 int sumsq = 0 ;
 int sum = 0 ;
 for ( i = - 8 ;
 i < 0 ;
 i ++ ) s [ i ] = s [ 0 ] ;
 for ( i = 0 ;
 i < 17 ;
 i ++ ) s [ i + cols ] = s [ cols - 1 ] ;
 for ( i = - 8 ;
 i <= 6 ;
 i ++ ) {
 sumsq += s [ i ] * s [ i ] ;
 sum += s [ i ] ;
 d [ i + 8 ] = 0 ;
 }
 for ( c = 0 ;
 c < cols + 8 ;
 c ++ ) {
 int x = s [ c + 7 ] - s [ c - 8 ] ;
 int y = s [ c + 7 ] + s [ c - 8 ] ;
 sum += x ;
 sumsq += x * y ;
 d [ c & 15 ] = s [ c ] ;
 if ( sumsq * 15 - sum * sum < flimit ) {
 d [ c & 15 ] = ( 8 + sum + s [ c ] ) >> 4 ;
 }
 s [ c - 8 ] = d [ ( c - 8 ) & 15 ] ;
 }
 s += pitch ;
 }
 }