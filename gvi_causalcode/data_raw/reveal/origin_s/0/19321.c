static void stabilize_lsps ( double * lsps , int num ) {
 int n , m , l ;
 lsps [ 0 ] = FFMAX ( lsps [ 0 ] , 0.0015 * M_PI ) ;
 for ( n = 1 ;
 n < num ;
 n ++ ) lsps [ n ] = FFMAX ( lsps [ n ] , lsps [ n - 1 ] + 0.0125 * M_PI ) ;
 lsps [ num - 1 ] = FFMIN ( lsps [ num - 1 ] , 0.9985 * M_PI ) ;
 for ( n = 1 ;
 n < num ;
 n ++ ) {
 if ( lsps [ n ] < lsps [ n - 1 ] ) {
 for ( m = 1 ;
 m < num ;
 m ++ ) {
 double tmp = lsps [ m ] ;
 for ( l = m - 1 ;
 l >= 0 ;
 l -- ) {
 if ( lsps [ l ] <= tmp ) break ;
 lsps [ l + 1 ] = lsps [ l ] ;
 }
 lsps [ l + 1 ] = tmp ;
 }
 break ;
 }
 }
 }