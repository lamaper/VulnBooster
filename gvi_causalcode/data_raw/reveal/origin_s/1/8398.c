static void _Latin1ToUnicodeWithOffsets ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 const uint8_t * source ;
 UChar * target ;
 int32_t targetCapacity , length ;
 int32_t * offsets ;
 int32_t sourceIndex ;
 source = ( const uint8_t * ) pArgs -> source ;
 target = pArgs -> target ;
 targetCapacity = ( int32_t ) ( pArgs -> targetLimit - pArgs -> target ) ;
 offsets = pArgs -> offsets ;
 sourceIndex = 0 ;
 length = ( int32_t ) ( ( const uint8_t * ) pArgs -> sourceLimit - source ) ;
 if ( length <= targetCapacity ) {
 targetCapacity = length ;
 }
 else {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 length = targetCapacity ;
 }
 if ( targetCapacity >= 8 ) {
 int32_t count , loops ;
 loops = count = targetCapacity >> 3 ;
 length = targetCapacity &= 0x7 ;
 do {
 target [ 0 ] = source [ 0 ] ;
 target [ 1 ] = source [ 1 ] ;
 target [ 2 ] = source [ 2 ] ;
 target [ 3 ] = source [ 3 ] ;
 target [ 4 ] = source [ 4 ] ;
 target [ 5 ] = source [ 5 ] ;
 target [ 6 ] = source [ 6 ] ;
 target [ 7 ] = source [ 7 ] ;
 target += 8 ;
 source += 8 ;
 }
 while ( -- count > 0 ) ;
 if ( offsets != NULL ) {
 do {
 offsets [ 0 ] = sourceIndex ++ ;
 offsets [ 1 ] = sourceIndex ++ ;
 offsets [ 2 ] = sourceIndex ++ ;
 offsets [ 3 ] = sourceIndex ++ ;
 offsets [ 4 ] = sourceIndex ++ ;
 offsets [ 5 ] = sourceIndex ++ ;
 offsets [ 6 ] = sourceIndex ++ ;
 offsets [ 7 ] = sourceIndex ++ ;
 offsets += 8 ;
 }
 while ( -- loops > 0 ) ;
 }
 }
 while ( targetCapacity > 0 ) {
 * target ++ = * source ++ ;
 -- targetCapacity ;
 }
 pArgs -> source = ( const char * ) source ;
 pArgs -> target = target ;
 if ( offsets != NULL ) {
 while ( length > 0 ) {
 * offsets ++ = sourceIndex ++ ;
 -- length ;
 }
 pArgs -> offsets = offsets ;
 }
 }