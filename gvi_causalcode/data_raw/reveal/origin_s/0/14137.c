int32_t rleStringToByteArray ( uint16_t * src , int32_t srcLen , uint8_t * target , int32_t tgtLen , UErrorCode * status ) {
 int32_t length = 0 ;
 UBool nextChar = TRUE ;
 uint16_t c = 0 ;
 int32_t node = 0 ;
 int32_t runLength = 0 ;
 int32_t i = 2 ;
 int32_t ai = 0 ;
 if ( ! status || U_FAILURE ( * status ) ) {
 return 0 ;
 }
 if ( srcLen == - 1 ) {
 srcLen = u_strlen ( src ) ;
 }
 if ( srcLen <= 2 ) {
 return 2 ;
 }
 length = ( ( ( int32_t ) src [ 0 ] ) << 16 ) | ( ( int32_t ) src [ 1 ] ) ;
 if ( target == NULL ) {
 return length ;
 }
 if ( tgtLen < length ) {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 return length ;
 }
 for ( ;
 ai < tgtLen ;
 ) {
 uint8_t b ;
 if ( nextChar ) {
 c = src [ i ++ ] ;
 b = ( uint8_t ) ( c >> 8 ) ;
 nextChar = FALSE ;
 }
 else {
 b = ( uint8_t ) ( c & 0xFF ) ;
 nextChar = TRUE ;
 }
 switch ( node ) {
 case 0 : if ( b == ESCAPE_BYTE ) {
 node = 1 ;
 }
 else {
 target [ ai ++ ] = b ;
 }
 break ;
 case 1 : if ( b == ESCAPE_BYTE ) {
 target [ ai ++ ] = ESCAPE_BYTE ;
 node = 0 ;
 }
 else {
 runLength = b ;
 node = 2 ;
 }
 break ;
 case 2 : {
 int j = 0 ;
 for ( ;
 j < runLength ;
 ++ j ) {
 if ( ai < tgtLen ) {
 target [ ai ++ ] = b ;
 }
 else {
 * status = U_BUFFER_OVERFLOW_ERROR ;
 return ai ;
 }
 }
 node = 0 ;
 break ;
 }
 }
 }
 if ( node != 0 ) {
 * status = U_INTERNAL_PROGRAM_ERROR ;
 return 0 ;
 }
 if ( i != srcLen ) {
 * status = U_INTERNAL_PROGRAM_ERROR ;
 return ai ;
 }
 return ai ;
 }