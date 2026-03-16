static float * calc_hist ( const float4 * hist , int nhist , int n ) {
 float * hist_part ;
 int k , i = 0 ;
 float prev_interval = 0 , next_interval ;
 float frac ;
 hist_part = ( float * ) palloc ( ( n + 1 ) * sizeof ( float ) ) ;
 frac = 1.0f / ( ( float ) ( nhist - 1 ) ) ;
 for ( k = 0 ;
 k <= n ;
 k ++ ) {
 int count = 0 ;
 while ( i < nhist && hist [ i ] <= k ) {
 count ++ ;
 i ++ ;
 }
 if ( count > 0 ) {
 float val ;
 if ( i < nhist ) next_interval = hist [ i ] - hist [ i - 1 ] ;
 else next_interval = 0 ;
 val = ( float ) ( count - 1 ) ;
 if ( next_interval > 0 ) val += 0.5f / next_interval ;
 if ( prev_interval > 0 ) val += 0.5f / prev_interval ;
 hist_part [ k ] = frac * val ;
 prev_interval = next_interval ;
 }
 else {
 if ( prev_interval > 0 ) hist_part [ k ] = frac / prev_interval ;
 else hist_part [ k ] = 0.0f ;
 }
 }
 return hist_part ;
 }