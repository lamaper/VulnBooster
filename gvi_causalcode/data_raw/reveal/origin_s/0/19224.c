static void U_CALLCONV _Latin1FromUnicodeWithOffsets ( UConverterFromUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 const UChar * source , * sourceLimit ;
 uint8_t * target , * oldTarget ;
 int32_t targetCapacity , length ;
 int32_t * offsets ;
 UChar32 cp ;
 UChar c , max ;
 int32_t sourceIndex ;
 cnv = pArgs -> converter ;
 source = pArgs -> source ;
 sourceLimit = pArgs -> sourceLimit ;
 target = oldTarget = ( uint8_t * ) pArgs -> target ;
 targetCapacity = ( int32_t ) ( pArgs -> targetLimit - pArgs -> target ) ;
 offsets = pArgs -> offsets ;
 if ( cnv -> sharedData == & _Latin1Data ) {
 max = 0xff ;
 }
 else {
 max = 0x7f ;
 }
 cp = cnv -> fromUChar32 ;
 sourceIndex = cp == 0 ? 0 : - 1 ;
 length = ( int32_t ) ( sourceLimit - source ) ;
 if ( length < targetCapacity ) {
 targetCapacity = length ;
 }
 if ( cp != 0 && targetCapacity > 0 ) {
 goto getTrail ;
 }

 int32_t count , loops ;
 UChar u , oredChars ;
 loops = count = targetCapacity >> 4 ;
 do {
 oredChars = u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 oredChars |= u = * source ++ ;
 * target ++ = ( uint8_t ) u ;
 if ( oredChars > max ) {
 source -= 16 ;
 target -= 16 ;
 break ;
 }
 }
 while ( -- count > 0 ) ;
 count = loops - count ;
 targetCapacity -= 16 * count ;
 if ( offsets != NULL ) {
 oldTarget += 16 * count ;
 while ( count > 0 ) {
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 * offsets ++ = sourceIndex ++ ;
 -- count ;
 }
 }
 }

 while ( targetCapacity > 0 && ( c = * source ++ ) <= max ) {
 * target ++ = ( uint8_t ) c ;
 -- targetCapacity ;
 }
 if ( c > max ) {
 cp = c ;
 if ( ! U_IS_SURROGATE ( cp ) ) {
 }
 else if ( U_IS_SURROGATE_LEAD ( cp ) ) {
 getTrail : if ( source < sourceLimit ) {
 UChar trail = * source ;
 if ( U16_IS_TRAIL ( trail ) ) {
 ++ source ;
 cp = U16_GET_SUPPLEMENTARY ( cp , trail ) ;
 }
 else {
 }
 }
 else {
 cnv -> fromUChar32 = cp ;
 goto noMoreInput ;
 }
 }
 else {
 }
 * pErrorCode = U_IS_SURROGATE ( cp ) ? U_ILLEGAL_CHAR_FOUND : U_INVALID_CHAR_FOUND ;
 cnv -> fromUChar32 = cp ;
 }
 noMoreInput : if ( offsets != NULL ) {
 size_t count = target - oldTarget ;
 while ( count > 0 ) {
 * offsets ++ = sourceIndex ++ ;
 -- count ;
 }
 }
 if ( U_SUCCESS ( * pErrorCode ) && source < sourceLimit && target >= ( uint8_t * ) pArgs -> targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 pArgs -> source = source ;
 pArgs -> target = ( char * ) target ;
 pArgs -> offsets = offsets ;
 }