static int32_t compareUnicode ( UCMTable * lTable , const UCMapping * l , UCMTable * rTable , const UCMapping * r ) {
 const UChar32 * lu , * ru ;
 int32_t result , i , length ;
 if ( l -> uLen == 1 && r -> uLen == 1 ) {
 return l -> u - r -> u ;
 }
 lu = UCM_GET_CODE_POINTS ( lTable , l ) ;
 ru = UCM_GET_CODE_POINTS ( rTable , r ) ;
 if ( l -> uLen <= r -> uLen ) {
 length = l -> uLen ;
 }
 else {
 length = r -> uLen ;
 }
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 result = lu [ i ] - ru [ i ] ;
 if ( result != 0 ) {
 return result ;
 }
 }
 return l -> uLen - r -> uLen ;
 }