static void fix_interp_filter ( VP9_COMMON * cm ) {
 if ( cm -> interp_filter == SWITCHABLE ) {
 int count [ SWITCHABLE_FILTERS ] ;
 int i , j , c = 0 ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTERS ;
 ++ i ) {
 count [ i ] = 0 ;
 for ( j = 0 ;
 j < SWITCHABLE_FILTER_CONTEXTS ;
 ++ j ) count [ i ] += cm -> counts . switchable_interp [ j ] [ i ] ;
 c += ( count [ i ] > 0 ) ;
 }
 if ( c == 1 ) {
 for ( i = 0 ;
 i < SWITCHABLE_FILTERS ;
 ++ i ) {
 if ( count [ i ] ) {
 cm -> interp_filter = i ;
 break ;
 }
 }
 }
 }
 }