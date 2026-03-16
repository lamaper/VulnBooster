int32_t rleStringToUCharArray ( uint16_t * src , int32_t srcLen , uint16_t * target , int32_t tgtLen , UErrorCode * status ) {
 int32_t length = 0 ;
 int32_t ai = 0 ;
 int i = 2 ;
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
 i < srcLen ;
 ++ i ) {
 uint16_t c = src [ i ] ;
 if ( c == ESCAPE ) {
 c = src [ ++ i ] ;
 if ( c == ESCAPE ) {
 target [ ai ++ ] = c ;
 }
 else {
 int32_t runLength = ( int32_t ) c ;
 uint16_t runValue = src [ ++ i ] ;
 int j = 0 ;
 for ( ;
 j < runLength ;
 ++ j ) {
 target [ ai ++ ] = runValue ;
 }
 }
 }
 else {
 target [ ai ++ ] = c ;
 }
 }
 if ( ai != length ) {
 * status = U_INTERNAL_PROGRAM_ERROR ;
 }
 return length ;
 }