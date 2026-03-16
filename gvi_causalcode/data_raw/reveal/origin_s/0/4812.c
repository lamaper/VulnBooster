static int32_t compareBytes ( UCMTable * lTable , const UCMapping * l , UCMTable * rTable , const UCMapping * r , UBool lexical ) {
 const uint8_t * lb , * rb ;
 int32_t result , i , length ;
 if ( lexical ) {
 if ( l -> bLen <= r -> bLen ) {
 length = l -> bLen ;
 }
 else {
 length = r -> bLen ;
 }
 }
 else {
 result = l -> bLen - r -> bLen ;
 if ( result != 0 ) {
 return result ;
 }
 else {
 length = l -> bLen ;
 }
 }
 lb = UCM_GET_BYTES ( lTable , l ) ;
 rb = UCM_GET_BYTES ( rTable , r ) ;
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 result = lb [ i ] - rb [ i ] ;
 if ( result != 0 ) {
 return result ;
 }
 }
 return l -> bLen - r -> bLen ;
 }