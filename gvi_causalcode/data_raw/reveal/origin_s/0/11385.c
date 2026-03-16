static uint32_t U_CALLCONV lenient8IteratorGetState ( const UCharIterator * iter ) {
 uint32_t state = ( uint32_t ) ( iter -> start << 1 ) ;
 if ( iter -> reservedField != 0 ) {
 state |= 1 ;
 }
 return state ;
 }