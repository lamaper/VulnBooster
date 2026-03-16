static void circlearcsto ( real a1 , real a2 , real cx , real cy , real r , SplineSet * cur , real * transform , int clockwise ) {
 int a ;
 real last ;
 while ( a1 < 0 ) {
 a1 += 360 ;
 a2 += 360 ;
 }
 while ( a2 - a1 <= - 360 ) a2 += 360 ;
 while ( a1 > 360 ) {
 a1 -= 360 ;
 a2 -= 360 ;
 }
 while ( a2 - a1 > 360 ) a2 -= 360 ;
 if ( ! clockwise ) {
 if ( a1 > a2 ) a2 += 360 ;
 last = a1 ;
 for ( a = ( ( int ) ( a1 + 90 ) / 90 ) * 90 ;
 a < a2 ;
 a += 90 ) {
 circlearcto ( last , a , cx , cy , r , cur , transform ) ;
 last = a ;
 }
 circlearcto ( last , a2 , cx , cy , r , cur , transform ) ;
 }
 else {
 if ( a2 > a1 ) a1 += 360 ;
 last = a1 ;
 for ( a = ( ( int ) ( a1 - 90 ) / 90 ) * 90 + 90 ;
 a > a2 ;
 a -= 90 ) {
 circlearcto ( last , a , cx , cy , r , cur , transform ) ;
 last = a ;
 }
 circlearcto ( last , a2 , cx , cy , r , cur , transform ) ;
 }
 }