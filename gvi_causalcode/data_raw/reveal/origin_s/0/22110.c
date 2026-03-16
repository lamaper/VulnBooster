void ufmt_ptou ( UChar * buffer , int32_t * len , void * value , UBool uselower ) {
 int32_t i ;
 int32_t length = 0 ;
 uint8_t * ptrIdx = ( uint8_t * ) & value ;

 i < ( int32_t ) sizeof ( void * ) ;
 i ++ ) # else for ( i = ( int32_t ) sizeof ( void * ) - 1 ;
 i >= 0 ;
 i -- ) # endif {
 uint8_t byteVal = ptrIdx [ i ] ;
 uint16_t firstNibble = ( uint16_t ) ( byteVal >> 4 ) ;
 uint16_t secondNibble = ( uint16_t ) ( byteVal & 0xF ) ;
 if ( uselower ) {
 buffer [ length ++ ] = TO_LC_DIGIT ( firstNibble ) ;
 buffer [ length ++ ] = TO_LC_DIGIT ( secondNibble ) ;
 }
 else {
 buffer [ length ++ ] = TO_UC_DIGIT ( firstNibble ) ;
 buffer [ length ++ ] = TO_UC_DIGIT ( secondNibble ) ;
 }
 }
 * len = length ;
 }