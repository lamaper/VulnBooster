static uint32_t write32 ( FileStream * out , uint32_t bitField , uint32_t column ) {
 int32_t i ;
 char bitFieldStr [ 64 ] ;
 char * s = bitFieldStr ;
 uint8_t * ptrIdx = ( uint8_t * ) & bitField ;
 static const char hexToStr [ 16 ] = {
 '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' }
 ;
 if ( column == MAX_COLUMN ) {
 column = 1 ;
 }
 else if ( column < 32 ) {
 * ( s ++ ) = ',' ;
 ++ column ;
 }
 else {
 * ( s ++ ) = '\n' ;
 uprv_strcpy ( s , assemblyHeader [ assemblyHeaderIndex ] . beginLine ) ;
 s += uprv_strlen ( s ) ;
 column = 1 ;
 }
 if ( bitField < 10 ) {
 * ( s ++ ) = hexToStr [ bitField ] ;
 }
 else {
 int seenNonZero = 0 ;
 if ( hexType == HEX_0X ) {
 * ( s ++ ) = '0' ;
 * ( s ++ ) = 'x' ;
 }
 else if ( hexType == HEX_0H ) {
 * ( s ++ ) = '0' ;
 }

 i < sizeof ( uint32_t ) ;
 i ++ ) # else for ( i = sizeof ( uint32_t ) - 1 ;
 i >= 0 ;
 i -- ) # endif {
 uint8_t value = ptrIdx [ i ] ;
 if ( value || seenNonZero ) {
 * ( s ++ ) = hexToStr [ value >> 4 ] ;
 * ( s ++ ) = hexToStr [ value & 0xF ] ;
 seenNonZero = 1 ;
 }
 }
 if ( hexType == HEX_0H ) {
 * ( s ++ ) = 'h' ;
 }
 }
 * ( s ++ ) = 0 ;
 T_FileStream_writeLine ( out , bitFieldStr ) ;
 return column ;
 }