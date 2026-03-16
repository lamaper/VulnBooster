static int32_t findNextEsc ( const char * source , const char * sourceLimit ) {
 int32_t length = sourceLimit - source ;
 int32_t i ;
 for ( i = 1 ;
 i < length ;
 i ++ ) {
 if ( * ( source + i ) == 0x1B ) {
 return i ;
 }
 }
 return length ;
 }