static UChar32 getMirror ( const UBiDiProps * bdp , UChar32 c , uint16_t props ) {
 int32_t delta = UBIDI_GET_MIRROR_DELTA ( props ) ;
 if ( delta != UBIDI_ESC_MIRROR_DELTA ) {
 return c + delta ;
 }
 else {
 const uint32_t * mirrors ;
 uint32_t m ;
 int32_t i , length ;
 UChar32 c2 ;
 mirrors = bdp -> mirrors ;
 length = bdp -> indexes [ UBIDI_IX_MIRROR_LENGTH ] ;
 for ( i = 0 ;
 i < length ;
 ++ i ) {
 m = mirrors [ i ] ;
 c2 = UBIDI_GET_MIRROR_CODE_POINT ( m ) ;
 if ( c == c2 ) {
 return UBIDI_GET_MIRROR_CODE_POINT ( mirrors [ UBIDI_GET_MIRROR_INDEX ( m ) ] ) ;
 }
 else if ( c < c2 ) {
 break ;
 }
 }
 return c ;
 }
 }