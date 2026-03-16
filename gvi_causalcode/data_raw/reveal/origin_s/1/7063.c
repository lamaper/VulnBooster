static UChar32 ucnv_getNextUChar_UTF8 ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 UConverter * cnv ;
 const uint8_t * sourceInitial ;
 const uint8_t * source ;
 uint16_t extraBytesToWrite ;
 uint8_t myByte ;
 UChar32 ch ;
 int8_t i , isLegalSequence ;
 cnv = args -> converter ;
 sourceInitial = source = ( const uint8_t * ) args -> source ;
 if ( source >= ( const uint8_t * ) args -> sourceLimit ) {
 * err = U_INDEX_OUTOFBOUNDS_ERROR ;
 return 0xffff ;
 }
 myByte = ( uint8_t ) * ( source ++ ) ;
 if ( myByte < 0x80 ) {
 args -> source = ( const char * ) source ;
 return ( UChar32 ) myByte ;
 }
 extraBytesToWrite = ( uint16_t ) bytesFromUTF8 [ myByte ] ;
 if ( extraBytesToWrite == 0 ) {
 cnv -> toUBytes [ 0 ] = myByte ;
 cnv -> toULength = 1 ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 args -> source = ( const char * ) source ;
 return 0xffff ;
 }
 if ( ( ( const char * ) source + extraBytesToWrite - 1 ) > args -> sourceLimit ) {
 cnv -> toUBytes [ 0 ] = myByte ;
 i = 1 ;
 * err = U_TRUNCATED_CHAR_FOUND ;
 while ( source < ( const uint8_t * ) args -> sourceLimit ) {
 if ( U8_IS_TRAIL ( myByte = * source ) ) {
 cnv -> toUBytes [ i ++ ] = myByte ;
 ++ source ;
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 }
 cnv -> toULength = i ;
 args -> source = ( const char * ) source ;
 return 0xffff ;
 }
 isLegalSequence = 1 ;
 ch = myByte << 6 ;
 switch ( extraBytesToWrite ) {
 case 6 : ch += ( myByte = * source ) ;
 ch <<= 6 ;
 if ( ! U8_IS_TRAIL ( myByte ) ) {
 isLegalSequence = 0 ;
 break ;
 }
 ++ source ;
 U_FALLTHROUGH ;
 case 5 : ch += ( myByte = * source ) ;
 ch <<= 6 ;
 if ( ! U8_IS_TRAIL ( myByte ) ) {
 isLegalSequence = 0 ;
 break ;
 }
 ++ source ;
 U_FALLTHROUGH ;
 case 4 : ch += ( myByte = * source ) ;
 ch <<= 6 ;
 if ( ! U8_IS_TRAIL ( myByte ) ) {
 isLegalSequence = 0 ;
 break ;
 }
 ++ source ;
 U_FALLTHROUGH ;
 case 3 : ch += ( myByte = * source ) ;
 ch <<= 6 ;
 if ( ! U8_IS_TRAIL ( myByte ) ) {
 isLegalSequence = 0 ;
 break ;
 }
 ++ source ;
 U_FALLTHROUGH ;
 case 2 : ch += ( myByte = * source ) ;
 if ( ! U8_IS_TRAIL ( myByte ) ) {
 isLegalSequence = 0 ;
 break ;
 }
 ++ source ;
 }
 ;
 ch -= offsetsFromUTF8 [ extraBytesToWrite ] ;
 args -> source = ( const char * ) source ;
 if ( isLegalSequence && ( uint32_t ) ch <= MAXIMUM_UTF && ( uint32_t ) ch >= utf8_minChar32 [ extraBytesToWrite ] && ! U_IS_SURROGATE ( ch ) ) {
 return ch ;
 }
 for ( i = 0 ;
 sourceInitial < source ;
 ++ i ) {
 cnv -> toUBytes [ i ] = * sourceInitial ++ ;
 }
 cnv -> toULength = i ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 return 0xffff ;
 }