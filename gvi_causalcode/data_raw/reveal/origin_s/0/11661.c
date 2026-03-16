static void U_CALLCONV _ASCIIToUnicodeWithOffsets ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 const uint8_t * source , * sourceLimit ;
 UChar * target , * oldTarget ;
 int32_t targetCapacity , length ;
 int32_t * offsets ;
 int32_t sourceIndex ;
 uint8_t c ;
 source = ( const uint8_t * ) pArgs -> source ;
 sourceLimit = ( const uint8_t * ) pArgs -> sourceLimit ;
 target = oldTarget = pArgs -> target ;
 targetCapacity = ( int32_t ) ( pArgs -> targetLimit - pArgs -> target ) ;
 offsets = pArgs -> offsets ;
 sourceIndex = 0 ;
 length = ( int32_t ) ( sourceLimit - source ) ;
 if ( length < targetCapacity ) {
 targetCapacity = length ;
 }
 if ( targetCapacity >= 8 ) {
 int32_t count , loops ;
 UChar oredChars ;
 loops = count = targetCapacity >> 3 ;
 do {
 oredChars = target [ 0 ] = source [ 0 ] ;
 oredChars |= target [ 1 ] = source [ 1 ] ;
 oredChars |= target [ 2 ] = source [ 2 ] ;
 oredChars |= target [ 3 ] = source [ 3 ] ;
 oredChars |= target [ 4 ] = source [ 4 ] ;
 oredChars |= target [ 5 ] = source [ 5 ] ;
 oredChars |= target [ 6 ] = source [ 6 ] ;
 oredChars |= target [ 7 ] = source [ 7 ] ;
 if ( oredChars > 0x7f ) {
 break ;
 }
 source += 8 ;
 target += 8 ;
 }
 while ( -- count > 0 ) ;
 count = loops - count ;
 targetCapacity -= count * 8 ;
 if ( offsets != NULL ) {
 oldTarget += count * 8 ;
 while ( count > 0 ) {
 offsets [ 0 ] = sourceIndex ++ ;
 offsets [ 1 ] = sourceIndex ++ ;
 offsets [ 2 ] = sourceIndex ++ ;
 offsets [ 3 ] = sourceIndex ++ ;
 offsets [ 4 ] = sourceIndex ++ ;
 offsets [ 5 ] = sourceIndex ++ ;
 offsets [ 6 ] = sourceIndex ++ ;
 offsets [ 7 ] = sourceIndex ++ ;
 offsets += 8 ;
 -- count ;
 }
 }
 }
 c = 0 ;
 while ( targetCapacity > 0 && ( c = * source ++ ) <= 0x7f ) {
 * target ++ = c ;
 -- targetCapacity ;
 }
 if ( c > 0x7f ) {
 UConverter * cnv = pArgs -> converter ;
 cnv -> toUBytes [ 0 ] = c ;
 cnv -> toULength = 1 ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 }
 else if ( source < sourceLimit && target >= pArgs -> targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 if ( offsets != NULL ) {
 size_t count = target - oldTarget ;
 while ( count > 0 ) {
 * offsets ++ = sourceIndex ++ ;
 -- count ;
 }
 }
 pArgs -> source = ( const char * ) source ;
 pArgs -> target = target ;
 pArgs -> offsets = offsets ;
 }