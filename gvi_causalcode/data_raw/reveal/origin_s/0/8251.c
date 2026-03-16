static void U_CALLCONV ucnv_toUnicode_UTF8 ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 UConverter * cnv = args -> converter ;
 const unsigned char * mySource = ( unsigned char * ) args -> source ;
 UChar * myTarget = args -> target ;
 const unsigned char * sourceLimit = ( unsigned char * ) args -> sourceLimit ;
 const UChar * targetLimit = args -> targetLimit ;
 unsigned char * toUBytes = cnv -> toUBytes ;
 UBool isCESU8 = hasCESU8Data ( cnv ) ;
 uint32_t ch , ch2 = 0 ;
 int32_t i , inBytes ;
 if ( cnv -> toUnicodeStatus && myTarget < targetLimit ) {
 inBytes = cnv -> mode ;
 i = cnv -> toULength ;
 cnv -> toULength = 0 ;
 ch = cnv -> toUnicodeStatus ;
 cnv -> toUnicodeStatus = 0 ;
 goto morebytes ;
 }
 while ( mySource < sourceLimit && myTarget < targetLimit ) {
 ch = * ( mySource ++ ) ;
 if ( ch < 0x80 ) {
 * ( myTarget ++ ) = ( UChar ) ch ;
 }
 else {
 toUBytes [ 0 ] = ( char ) ch ;
 inBytes = bytesFromUTF8 [ ch ] ;
 i = 1 ;
 morebytes : while ( i < inBytes ) {
 if ( mySource < sourceLimit ) {
 toUBytes [ i ] = ( char ) ( ch2 = * mySource ) ;
 if ( ! U8_IS_TRAIL ( ch2 ) ) {
 break ;
 }
 ch = ( ch << 6 ) + ch2 ;
 ++ mySource ;
 i ++ ;
 }
 else {
 cnv -> toUnicodeStatus = ch ;
 cnv -> mode = inBytes ;
 cnv -> toULength = ( int8_t ) i ;
 goto donefornow ;
 }
 }
 ch -= offsetsFromUTF8 [ inBytes ] ;
 if ( i == inBytes && ch <= MAXIMUM_UTF && ch >= utf8_minChar32 [ i ] && ( isCESU8 ? i <= 3 : ! U_IS_SURROGATE ( ch ) ) ) {
 if ( ch <= MAXIMUM_UCS2 ) {
 * ( myTarget ++ ) = ( UChar ) ch ;
 }
 else {
 ch -= HALF_BASE ;
 * ( myTarget ++ ) = ( UChar ) ( ( ch >> HALF_SHIFT ) + SURROGATE_HIGH_START ) ;
 ch = ( ch & HALF_MASK ) + SURROGATE_LOW_START ;
 if ( myTarget < targetLimit ) {
 * ( myTarget ++ ) = ( UChar ) ch ;
 }
 else {
 cnv -> UCharErrorBuffer [ 0 ] = ( UChar ) ch ;
 cnv -> UCharErrorBufferLength = 1 ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 }
 else {
 cnv -> toULength = ( int8_t ) i ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 }
 }
 donefornow : if ( mySource < sourceLimit && myTarget >= targetLimit && U_SUCCESS ( * err ) ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 args -> target = myTarget ;
 args -> source = ( const char * ) mySource ;
 }