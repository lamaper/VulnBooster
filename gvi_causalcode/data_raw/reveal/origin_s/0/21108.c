static void U_CALLCONV _SCSUToUnicode ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 SCSUData * scsu ;
 const uint8_t * source , * sourceLimit ;
 UChar * target ;
 const UChar * targetLimit ;
 UBool isSingleByteMode ;
 uint8_t state , byteOne ;
 int8_t quoteWindow , dynamicWindow ;
 uint8_t b ;
 cnv = pArgs -> converter ;
 scsu = ( SCSUData * ) cnv -> extraInfo ;
 source = ( const uint8_t * ) pArgs -> source ;
 sourceLimit = ( const uint8_t * ) pArgs -> sourceLimit ;
 target = pArgs -> target ;
 targetLimit = pArgs -> targetLimit ;
 isSingleByteMode = scsu -> toUIsSingleByteMode ;
 state = scsu -> toUState ;
 quoteWindow = scsu -> toUQuoteWindow ;
 dynamicWindow = scsu -> toUDynamicWindow ;
 byteOne = scsu -> toUByteOne ;
 if ( isSingleByteMode ) {
 if ( state == readCommand ) {
 fastSingle : while ( source < sourceLimit && target < targetLimit && ( b = * source ) >= 0x20 ) {
 ++ source ;
 if ( b <= 0x7f ) {
 * target ++ = ( UChar ) b ;
 }
 else {
 uint32_t c = scsu -> toUDynamicOffsets [ dynamicWindow ] + ( b & 0x7f ) ;
 if ( c <= 0xffff ) {
 * target ++ = ( UChar ) c ;
 }
 else {
 * target ++ = ( UChar ) ( 0xd7c0 + ( c >> 10 ) ) ;
 if ( target < targetLimit ) {
 * target ++ = ( UChar ) ( 0xdc00 | ( c & 0x3ff ) ) ;
 }
 else {
 cnv -> UCharErrorBuffer [ 0 ] = ( UChar ) ( 0xdc00 | ( c & 0x3ff ) ) ;
 cnv -> UCharErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 goto endloop ;
 }
 }
 }
 }
 }
 singleByteMode : while ( source < sourceLimit ) {
 if ( target >= targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 b = * source ++ ;
 switch ( state ) {
 case readCommand : if ( ( 1UL << b ) & 0x2601 ) {
 * target ++ = ( UChar ) b ;
 goto fastSingle ;
 }
 else if ( SC0 <= b ) {
 if ( b <= SC7 ) {
 dynamicWindow = ( int8_t ) ( b - SC0 ) ;
 goto fastSingle ;
 }
 else {
 dynamicWindow = ( int8_t ) ( b - SD0 ) ;
 state = defineOne ;
 }
 }
 else if ( b <= SQ7 ) {
 quoteWindow = ( int8_t ) ( b - SQ0 ) ;
 state = quoteOne ;
 }
 else if ( b == SDX ) {
 state = definePairOne ;
 }
 else if ( b == SQU ) {
 state = quotePairOne ;
 }
 else if ( b == SCU ) {
 isSingleByteMode = FALSE ;
 goto fastUnicode ;
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 goto endloop ;
 }
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 break ;
 case quotePairOne : byteOne = b ;
 cnv -> toUBytes [ 1 ] = b ;
 cnv -> toULength = 2 ;
 state = quotePairTwo ;
 break ;
 case quotePairTwo : * target ++ = ( UChar ) ( ( byteOne << 8 ) | b ) ;
 state = readCommand ;
 goto fastSingle ;
 case quoteOne : if ( b < 0x80 ) {
 * target ++ = ( UChar ) ( staticOffsets [ quoteWindow ] + b ) ;
 }
 else {
 uint32_t c = scsu -> toUDynamicOffsets [ quoteWindow ] + ( b & 0x7f ) ;
 if ( c <= 0xffff ) {
 * target ++ = ( UChar ) c ;
 }
 else {
 * target ++ = ( UChar ) ( 0xd7c0 + ( c >> 10 ) ) ;
 if ( target < targetLimit ) {
 * target ++ = ( UChar ) ( 0xdc00 | ( c & 0x3ff ) ) ;
 }
 else {
 cnv -> UCharErrorBuffer [ 0 ] = ( UChar ) ( 0xdc00 | ( c & 0x3ff ) ) ;
 cnv -> UCharErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 goto endloop ;
 }
 }
 }
 state = readCommand ;
 goto fastSingle ;
 case definePairOne : dynamicWindow = ( int8_t ) ( ( b >> 5 ) & 7 ) ;
 byteOne = ( uint8_t ) ( b & 0x1f ) ;
 cnv -> toUBytes [ 1 ] = b ;
 cnv -> toULength = 2 ;
 state = definePairTwo ;
 break ;
 case definePairTwo : scsu -> toUDynamicOffsets [ dynamicWindow ] = 0x10000 + ( byteOne << 15UL | b << 7UL ) ;
 state = readCommand ;
 goto fastSingle ;
 case defineOne : if ( b == 0 ) {
 cnv -> toUBytes [ 1 ] = b ;
 cnv -> toULength = 2 ;
 goto endloop ;
 }
 else if ( b < gapThreshold ) {
 scsu -> toUDynamicOffsets [ dynamicWindow ] = b << 7UL ;
 }
 else if ( ( uint8_t ) ( b - gapThreshold ) < ( reservedStart - gapThreshold ) ) {
 scsu -> toUDynamicOffsets [ dynamicWindow ] = ( b << 7UL ) + gapOffset ;
 }
 else if ( b >= fixedThreshold ) {
 scsu -> toUDynamicOffsets [ dynamicWindow ] = fixedOffsets [ b - fixedThreshold ] ;
 }
 else {
 cnv -> toUBytes [ 1 ] = b ;
 cnv -> toULength = 2 ;
 goto endloop ;
 }
 state = readCommand ;
 goto fastSingle ;
 }
 }
 }
 else {
 if ( state == readCommand ) {
 fastUnicode : while ( source + 1 < sourceLimit && target < targetLimit && ( uint8_t ) ( ( b = * source ) - UC0 ) > ( Urs - UC0 ) ) {
 * target ++ = ( UChar ) ( ( b << 8 ) | source [ 1 ] ) ;
 source += 2 ;
 }
 }
 while ( source < sourceLimit ) {
 if ( target >= targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 b = * source ++ ;
 switch ( state ) {
 case readCommand : if ( ( uint8_t ) ( b - UC0 ) > ( Urs - UC0 ) ) {
 byteOne = b ;
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 state = quotePairTwo ;
 }
 else if ( b <= UC7 ) {
 dynamicWindow = ( int8_t ) ( b - UC0 ) ;
 isSingleByteMode = TRUE ;
 goto fastSingle ;
 }
 else if ( b <= UD7 ) {
 dynamicWindow = ( int8_t ) ( b - UD0 ) ;
 isSingleByteMode = TRUE ;
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 state = defineOne ;
 goto singleByteMode ;
 }
 else if ( b == UDX ) {
 isSingleByteMode = TRUE ;
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 state = definePairOne ;
 goto singleByteMode ;
 }
 else if ( b == UQU ) {
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 state = quotePairOne ;
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 goto endloop ;
 }
 break ;
 case quotePairOne : byteOne = b ;
 cnv -> toUBytes [ 1 ] = b ;
 cnv -> toULength = 2 ;
 state = quotePairTwo ;
 break ;
 case quotePairTwo : * target ++ = ( UChar ) ( ( byteOne << 8 ) | b ) ;
 state = readCommand ;
 goto fastUnicode ;
 }
 }
 }
 endloop : if ( U_FAILURE ( * pErrorCode ) && * pErrorCode != U_BUFFER_OVERFLOW_ERROR ) {
 state = readCommand ;
 }
 else if ( state == readCommand ) {
 cnv -> toULength = 0 ;
 }
 scsu -> toUIsSingleByteMode = isSingleByteMode ;
 scsu -> toUState = state ;
 scsu -> toUQuoteWindow = quoteWindow ;
 scsu -> toUDynamicWindow = dynamicWindow ;
 scsu -> toUByteOne = byteOne ;
 pArgs -> source = ( const char * ) source ;
 pArgs -> target = target ;
 return ;
 }