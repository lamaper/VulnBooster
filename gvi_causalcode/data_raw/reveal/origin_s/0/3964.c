static int32_t U_CALLCONV upvec_compareRows ( const void * context , const void * l , const void * r ) {
 const uint32_t * left = ( const uint32_t * ) l , * right = ( const uint32_t * ) r ;
 const UPropsVectors * pv = ( const UPropsVectors * ) context ;
 int32_t i , count , columns ;
 count = columns = pv -> columns ;
 i = 2 ;
 do {
 if ( left [ i ] != right [ i ] ) {
 return left [ i ] < right [ i ] ? - 1 : 1 ;
 }
 if ( ++ i == columns ) {
 i = 0 ;
 }
 }
 while ( -- count > 0 ) ;
 return 0 ;
 }