void vp8_mbpost_proc_down_c ( unsigned char * dst , int pitch , int rows , int cols , int flimit ) {
 int r , c , i ;
 const short * rv3 = & vp8_rv [ 63 & rand ( ) ] ;
 for ( c = 0 ;
 c < cols ;
 c ++ ) {
 unsigned char * s = & dst [ c ] ;
 int sumsq = 0 ;
 int sum = 0 ;
 unsigned char d [ 16 ] ;
 const short * rv2 = rv3 + ( ( c * 17 ) & 127 ) ;
 for ( i = - 8 ;
 i < 0 ;
 i ++ ) s [ i * pitch ] = s [ 0 ] ;
 for ( i = rows ;
 i < rows + 17 ;
 i ++ ) s [ i * pitch ] = s [ ( rows - 1 ) * pitch ] ;
 for ( i = - 8 ;
 i <= 6 ;
 i ++ ) {
 sumsq += s [ i * pitch ] * s [ i * pitch ] ;
 sum += s [ i * pitch ] ;
 }
 for ( r = 0 ;
 r < rows + 8 ;
 r ++ ) {
 sumsq += s [ 7 * pitch ] * s [ 7 * pitch ] - s [ - 8 * pitch ] * s [ - 8 * pitch ] ;
 sum += s [ 7 * pitch ] - s [ - 8 * pitch ] ;
 d [ r & 15 ] = s [ 0 ] ;
 if ( sumsq * 15 - sum * sum < flimit ) {
 d [ r & 15 ] = ( rv2 [ r & 127 ] + sum + s [ 0 ] ) >> 4 ;
 }
 if ( r >= 8 ) s [ - 8 * pitch ] = d [ ( r - 8 ) & 15 ] ;
 s += pitch ;
 }
 }
 }