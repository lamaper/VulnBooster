void * ufmt_utop ( const UChar * buffer , int32_t * len ) {
 int32_t count , resultIdx , incVal , offset ;
 union {
 void * ptr ;
 uint8_t bytes [ sizeof ( void * ) ] ;
 }
 result ;
 count = 0 ;
 offset = 0 ;
 result . ptr = NULL ;
 while ( buffer [ count ] == DIGIT_0 || u_isspace ( buffer [ count ] ) ) {
 count ++ ;
 offset ++ ;
 }
 while ( ufmt_isdigit ( buffer [ count ] , 16 ) && count < * len ) {
 ++ count ;
 }
 if ( count - offset > ( int32_t ) ( sizeof ( void * ) * NIBBLE_PER_BYTE ) ) {
 offset = count - ( int32_t ) ( sizeof ( void * ) * NIBBLE_PER_BYTE ) ;
 }

 resultIdx = ( int32_t ) ( sizeof ( void * ) - 1 ) ;

 resultIdx = 0 ;

 while ( -- count >= offset ) {
 uint8_t byte = ( uint8_t ) ufmt_digitvalue ( buffer [ count ] ) ;
 if ( count > offset ) {
 byte = ( uint8_t ) ( byte + ( ufmt_digitvalue ( buffer [ -- count ] ) << 4 ) ) ;
 }
 result . bytes [ resultIdx ] = byte ;
 resultIdx += incVal ;
 }
 return result . ptr ;
 }