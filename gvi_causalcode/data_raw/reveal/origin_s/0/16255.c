static inline int median4 ( int a , int b , int c , int d ) {
 if ( a < b ) {
 if ( c < d ) return ( FFMIN ( b , d ) + FFMAX ( a , c ) ) / 2 ;
 else return ( FFMIN ( b , c ) + FFMAX ( a , d ) ) / 2 ;
 }
 else {
 if ( c < d ) return ( FFMIN ( a , d ) + FFMAX ( b , c ) ) / 2 ;
 else return ( FFMIN ( a , c ) + FFMAX ( b , d ) ) / 2 ;
 }
 }