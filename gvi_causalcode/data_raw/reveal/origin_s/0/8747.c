static void U_CALLCONV _SCSUFromUnicodeWithOffsets ( UConverterFromUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 SCSUData * scsu ;
 const UChar * source , * sourceLimit ;
 uint8_t * target ;
 int32_t targetCapacity ;
 int32_t * offsets ;
 UBool isSingleByteMode ;
 uint8_t dynamicWindow ;
 uint32_t currentOffset ;
 uint32_t c , delta ;
 int32_t sourceIndex , nextSourceIndex ;
 int32_t length ;
 uint32_t offset ;
 UChar lead , trail ;
 int code ;
 int8_t window ;
 cnv = pArgs -> converter ;
 scsu = ( SCSUData * ) cnv -> extraInfo ;
 source = pArgs -> source ;
 sourceLimit = pArgs -> sourceLimit ;
 target = ( uint8_t * ) pArgs -> target ;
 targetCapacity = ( int32_t ) ( pArgs -> targetLimit - pArgs -> target ) ;
 offsets = pArgs -> offsets ;
 isSingleByteMode = scsu -> fromUIsSingleByteMode ;
 dynamicWindow = scsu -> fromUDynamicWindow ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] ;
 c = cnv -> fromUChar32 ;
 sourceIndex = c == 0 ? 0 : - 1 ;
 nextSourceIndex = 0 ;
 loop : if ( isSingleByteMode ) {
 if ( c != 0 && targetCapacity > 0 ) {
 goto getTrailSingle ;
 }
 while ( source < sourceLimit ) {
 if ( targetCapacity <= 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 c = * source ++ ;
 ++ nextSourceIndex ;
 if ( ( c - 0x20 ) <= 0x5f ) {
 * target ++ = ( uint8_t ) c ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 -- targetCapacity ;
 }
 else if ( c < 0x20 ) {
 if ( ( 1UL << c ) & 0x2601 ) {
 * target ++ = ( uint8_t ) c ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 -- targetCapacity ;
 }
 else {
 c |= SQ0 << 8 ;
 length = 2 ;
 goto outputBytes ;
 }
 }
 else if ( ( delta = c - currentOffset ) <= 0x7f ) {
 * target ++ = ( uint8_t ) ( delta | 0x80 ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 -- targetCapacity ;
 }
 else if ( U16_IS_SURROGATE ( c ) ) {
 if ( U16_IS_SURROGATE_LEAD ( c ) ) {
 getTrailSingle : lead = ( UChar ) c ;
 if ( source < sourceLimit ) {
 trail = * source ;
 if ( U16_IS_TRAIL ( trail ) ) {
 ++ source ;
 ++ nextSourceIndex ;
 c = U16_GET_SUPPLEMENTARY ( c , trail ) ;
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 goto endloop ;
 }
 }
 else {
 break ;
 }
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 goto endloop ;
 }
 if ( ( delta = c - currentOffset ) <= 0x7f ) {
 * target ++ = ( uint8_t ) ( delta | 0x80 ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 -- targetCapacity ;
 }
 else if ( ( window = getWindow ( scsu -> fromUDynamicOffsets , c ) ) >= 0 ) {
 dynamicWindow = window ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) ( SC0 + dynamicWindow ) << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 2 ;
 goto outputBytes ;
 }
 else if ( ( code = getDynamicOffset ( c , & offset ) ) >= 0 ) {
 code -= 0x200 ;
 dynamicWindow = getNextDynamicWindow ( scsu ) ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] = offset ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) SDX << 24 ) | ( ( uint32_t ) dynamicWindow << 21 ) | ( ( uint32_t ) code << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 4 ;
 goto outputBytes ;
 }
 else {
 isSingleByteMode = FALSE ;
 * target ++ = ( uint8_t ) SCU ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 -- targetCapacity ;
 c = ( ( uint32_t ) lead << 16 ) | trail ;
 length = 4 ;
 goto outputBytes ;
 }
 }
 else if ( c < 0xa0 ) {
 c = ( c & 0x7f ) | ( SQ0 + 1 ) << 8 ;
 length = 2 ;
 goto outputBytes ;
 }
 else if ( c == 0xfeff || c >= 0xfff0 ) {
 c |= SQU << 16 ;
 length = 3 ;
 goto outputBytes ;
 }
 else {
 if ( ( window = getWindow ( scsu -> fromUDynamicOffsets , c ) ) >= 0 ) {
 if ( source >= sourceLimit || isInOffsetWindowOrDirect ( scsu -> fromUDynamicOffsets [ window ] , * source ) ) {
 dynamicWindow = window ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) ( SC0 + dynamicWindow ) << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 2 ;
 goto outputBytes ;
 }
 else {
 c = ( ( uint32_t ) ( SQ0 + window ) << 8 ) | ( c - scsu -> fromUDynamicOffsets [ window ] ) | 0x80 ;
 length = 2 ;
 goto outputBytes ;
 }
 }
 else if ( ( window = getWindow ( staticOffsets , c ) ) >= 0 ) {
 c = ( ( uint32_t ) ( SQ0 + window ) << 8 ) | ( c - staticOffsets [ window ] ) ;
 length = 2 ;
 goto outputBytes ;
 }
 else if ( ( code = getDynamicOffset ( c , & offset ) ) >= 0 ) {
 dynamicWindow = getNextDynamicWindow ( scsu ) ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] = offset ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) ( SD0 + dynamicWindow ) << 16 ) | ( ( uint32_t ) code << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 3 ;
 goto outputBytes ;
 }
 else if ( ( uint32_t ) ( c - 0x3400 ) < ( 0xd800 - 0x3400 ) && ( source >= sourceLimit || ( uint32_t ) ( * source - 0x3400 ) < ( 0xd800 - 0x3400 ) ) ) {
 isSingleByteMode = FALSE ;
 c |= SCU << 16 ;
 length = 3 ;
 goto outputBytes ;
 }
 else {
 c |= SQU << 16 ;
 length = 3 ;
 goto outputBytes ;
 }
 }
 c = 0 ;
 sourceIndex = nextSourceIndex ;
 }
 }
 else {
 if ( c != 0 && targetCapacity > 0 ) {
 goto getTrailUnicode ;
 }
 while ( source < sourceLimit ) {
 if ( targetCapacity <= 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 c = * source ++ ;
 ++ nextSourceIndex ;
 if ( ( uint32_t ) ( c - 0x3400 ) < ( 0xd800 - 0x3400 ) ) {
 if ( targetCapacity >= 2 ) {
 * target ++ = ( uint8_t ) ( c >> 8 ) ;
 * target ++ = ( uint8_t ) c ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 }
 targetCapacity -= 2 ;
 }
 else {
 length = 2 ;
 goto outputBytes ;
 }
 }
 else if ( ( uint32_t ) ( c - 0x3400 ) >= ( 0xf300 - 0x3400 ) ) {
 if ( ! ( source < sourceLimit && ( uint32_t ) ( * source - 0x3400 ) < ( 0xd800 - 0x3400 ) ) ) {
 if ( ( ( uint32_t ) ( c - 0x30 ) < 10 || ( uint32_t ) ( c - 0x61 ) < 26 || ( uint32_t ) ( c - 0x41 ) < 26 ) ) {
 isSingleByteMode = TRUE ;
 c |= ( ( uint32_t ) ( UC0 + dynamicWindow ) << 8 ) | c ;
 length = 2 ;
 goto outputBytes ;
 }
 else if ( ( window = getWindow ( scsu -> fromUDynamicOffsets , c ) ) >= 0 ) {
 isSingleByteMode = TRUE ;
 dynamicWindow = window ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) ( UC0 + dynamicWindow ) << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 2 ;
 goto outputBytes ;
 }
 else if ( ( code = getDynamicOffset ( c , & offset ) ) >= 0 ) {
 isSingleByteMode = TRUE ;
 dynamicWindow = getNextDynamicWindow ( scsu ) ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] = offset ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) ( UD0 + dynamicWindow ) << 16 ) | ( ( uint32_t ) code << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 3 ;
 goto outputBytes ;
 }
 }
 length = 2 ;
 goto outputBytes ;
 }
 else if ( c < 0xe000 ) {
 if ( U16_IS_SURROGATE_LEAD ( c ) ) {
 getTrailUnicode : lead = ( UChar ) c ;
 if ( source < sourceLimit ) {
 trail = * source ;
 if ( U16_IS_TRAIL ( trail ) ) {
 ++ source ;
 ++ nextSourceIndex ;
 c = U16_GET_SUPPLEMENTARY ( c , trail ) ;
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 goto endloop ;
 }
 }
 else {
 break ;
 }
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 goto endloop ;
 }
 if ( ( window = getWindow ( scsu -> fromUDynamicOffsets , c ) ) >= 0 && ! ( source < sourceLimit && ( uint32_t ) ( * source - 0x3400 ) < ( 0xd800 - 0x3400 ) ) ) {
 isSingleByteMode = TRUE ;
 dynamicWindow = window ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) ( UC0 + dynamicWindow ) << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 2 ;
 goto outputBytes ;
 }
 else if ( source < sourceLimit && lead == * source && ( code = getDynamicOffset ( c , & offset ) ) >= 0 ) {
 isSingleByteMode = TRUE ;
 code -= 0x200 ;
 dynamicWindow = getNextDynamicWindow ( scsu ) ;
 currentOffset = scsu -> fromUDynamicOffsets [ dynamicWindow ] = offset ;
 useDynamicWindow ( scsu , dynamicWindow ) ;
 c = ( ( uint32_t ) UDX << 24 ) | ( ( uint32_t ) dynamicWindow << 21 ) | ( ( uint32_t ) code << 8 ) | ( c - currentOffset ) | 0x80 ;
 length = 4 ;
 goto outputBytes ;
 }
 else {
 c = ( ( uint32_t ) lead << 16 ) | trail ;
 length = 4 ;
 goto outputBytes ;
 }
 }
 else {
 c |= UQU << 16 ;
 length = 3 ;
 goto outputBytes ;
 }
 c = 0 ;
 sourceIndex = nextSourceIndex ;
 }
 }
 endloop : scsu -> fromUIsSingleByteMode = isSingleByteMode ;
 scsu -> fromUDynamicWindow = dynamicWindow ;
 cnv -> fromUChar32 = c ;
 pArgs -> source = source ;
 pArgs -> target = ( char * ) target ;
 pArgs -> offsets = offsets ;
 return ;
 outputBytes : if ( length <= targetCapacity ) {
 if ( offsets == NULL ) {
 switch ( length ) {
 case 4 : * target ++ = ( uint8_t ) ( c >> 24 ) ;
 U_FALLTHROUGH ;
 case 3 : * target ++ = ( uint8_t ) ( c >> 16 ) ;
 U_FALLTHROUGH ;
 case 2 : * target ++ = ( uint8_t ) ( c >> 8 ) ;
 U_FALLTHROUGH ;
 case 1 : * target ++ = ( uint8_t ) c ;
 U_FALLTHROUGH ;
 default : break ;
 }
 }
 else {
 switch ( length ) {
 case 4 : * target ++ = ( uint8_t ) ( c >> 24 ) ;
 * offsets ++ = sourceIndex ;
 U_FALLTHROUGH ;
 case 3 : * target ++ = ( uint8_t ) ( c >> 16 ) ;
 * offsets ++ = sourceIndex ;
 U_FALLTHROUGH ;
 case 2 : * target ++ = ( uint8_t ) ( c >> 8 ) ;
 * offsets ++ = sourceIndex ;
 U_FALLTHROUGH ;
 case 1 : * target ++ = ( uint8_t ) c ;
 * offsets ++ = sourceIndex ;
 U_FALLTHROUGH ;
 default : break ;
 }
 }
 targetCapacity -= length ;
 c = 0 ;
 sourceIndex = nextSourceIndex ;
 goto loop ;
 }
 else {
 uint8_t * p ;
 length -= targetCapacity ;
 p = ( uint8_t * ) cnv -> charErrorBuffer ;
 switch ( length ) {
 case 4 : * p ++ = ( uint8_t ) ( c >> 24 ) ;
 U_FALLTHROUGH ;
 case 3 : * p ++ = ( uint8_t ) ( c >> 16 ) ;
 U_FALLTHROUGH ;
 case 2 : * p ++ = ( uint8_t ) ( c >> 8 ) ;
 U_FALLTHROUGH ;
 case 1 : * p = ( uint8_t ) c ;
 U_FALLTHROUGH ;
 default : break ;
 }
 cnv -> charErrorBufferLength = ( int8_t ) length ;
 c >>= 8 * length ;
 switch ( targetCapacity ) {
 case 3 : * target ++ = ( uint8_t ) ( c >> 16 ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 U_FALLTHROUGH ;
 case 2 : * target ++ = ( uint8_t ) ( c >> 8 ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 U_FALLTHROUGH ;
 case 1 : * target ++ = ( uint8_t ) c ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 U_FALLTHROUGH ;
 default : break ;
 }
 targetCapacity = 0 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 c = 0 ;
 goto endloop ;
 }
 }