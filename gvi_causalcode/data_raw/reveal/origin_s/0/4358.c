static int32_t compareMappings ( UCMTable * lTable , const UCMapping * l , UCMTable * rTable , const UCMapping * r , UBool uFirst ) {
 int32_t result ;
 if ( uFirst ) {
 result = compareUnicode ( lTable , l , rTable , r ) ;
 if ( result == 0 ) {
 result = compareBytes ( lTable , l , rTable , r , FALSE ) ;
 }
 }
 else {
 result = compareBytes ( lTable , l , rTable , r , TRUE ) ;
 if ( result == 0 ) {
 result = compareUnicode ( lTable , l , rTable , r ) ;
 }
 }
 if ( result != 0 ) {
 return result ;
 }
 return l -> f - r -> f ;
 }