static UBool ucnv_outputOverflowToUnicode ( UConverter * cnv , UChar * * target , const UChar * targetLimit , int32_t * * pOffsets , UErrorCode * err ) {
 int32_t * offsets ;
 UChar * overflow , * t ;
 int32_t i , length ;
 t = * target ;
 if ( pOffsets != NULL ) {
 offsets = * pOffsets ;
 }
 else {
 offsets = NULL ;
 }
 overflow = cnv -> UCharErrorBuffer ;
 length = cnv -> UCharErrorBufferLength ;
 i = 0 ;
 while ( i < length ) {
 if ( t == targetLimit ) {
 int32_t j = 0 ;
 do {
 overflow [ j ++ ] = overflow [ i ++ ] ;
 }
 while ( i < length ) ;
 cnv -> UCharErrorBufferLength = ( int8_t ) j ;
 * target = t ;
 if ( offsets != NULL ) {
 * pOffsets = offsets ;
 }
 * err = U_BUFFER_OVERFLOW_ERROR ;
 return TRUE ;
 }
 * t ++ = overflow [ i ++ ] ;
 if ( offsets != NULL ) {
 * offsets ++ = - 1 ;
 }
 }
 cnv -> UCharErrorBufferLength = 0 ;
 * target = t ;
 if ( offsets != NULL ) {
 * pOffsets = offsets ;
 }
 return FALSE ;
 }