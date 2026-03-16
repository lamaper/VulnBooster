static void fillrd ( struct postproc_state * state , int q , int a ) {
 char char_dist [ 300 ] ;
 double sigma ;
 int i ;
 vp8_clear_system_state ( ) ;
 sigma = a + .5 + .6 * ( 63 - q ) / 63.0 ;
 {
 int next , j ;
 next = 0 ;
 for ( i = - 32 ;
 i < 32 ;
 i ++ ) {
 const int v = ( int ) ( .5 + 256 * vp8_gaussian ( sigma , 0 , i ) ) ;
 if ( v ) {
 for ( j = 0 ;
 j < v ;
 j ++ ) {
 char_dist [ next + j ] = ( char ) i ;
 }
 next = next + j ;
 }
 }
 for ( ;
 next < 256 ;
 next ++ ) char_dist [ next ] = 0 ;
 }
 for ( i = 0 ;
 i < 3072 ;
 i ++ ) {
 state -> noise [ i ] = char_dist [ rand ( ) & 0xff ] ;
 }
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 state -> blackclamp [ i ] = - char_dist [ 0 ] ;
 state -> whiteclamp [ i ] = - char_dist [ 0 ] ;
 state -> bothclamp [ i ] = - 2 * char_dist [ 0 ] ;
 }
 state -> last_q = q ;
 state -> last_noise = a ;
 }