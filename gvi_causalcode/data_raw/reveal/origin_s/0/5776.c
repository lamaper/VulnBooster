static int32_t doWriteReverse ( const UChar * src , int32_t srcLength , UChar * dest , int32_t destSize , uint16_t options , UErrorCode * pErrorCode ) {
 int32_t i , j ;
 UChar32 c ;
 switch ( options & ( UBIDI_REMOVE_BIDI_CONTROLS | UBIDI_DO_MIRRORING | UBIDI_KEEP_BASE_COMBINING ) ) {
 case 0 : if ( destSize < srcLength ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return srcLength ;
 }
 destSize = srcLength ;
 do {
 i = srcLength ;
 U16_BACK_1 ( src , 0 , srcLength ) ;
 j = srcLength ;
 do {
 * dest ++ = src [ j ++ ] ;
 }
 while ( j < i ) ;
 }
 while ( srcLength > 0 ) ;
 break ;
 case UBIDI_KEEP_BASE_COMBINING : if ( destSize < srcLength ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return srcLength ;
 }
 destSize = srcLength ;
 do {
 i = srcLength ;
 do {
 U16_PREV ( src , 0 , srcLength , c ) ;
 }
 while ( srcLength > 0 && IS_COMBINING ( u_charType ( c ) ) ) ;
 j = srcLength ;
 do {
 * dest ++ = src [ j ++ ] ;
 }
 while ( j < i ) ;
 }
 while ( srcLength > 0 ) ;
 break ;
 default : if ( ! ( options & UBIDI_REMOVE_BIDI_CONTROLS ) ) {
 i = srcLength ;
 }
 else {
 int32_t length = srcLength ;
 UChar ch ;
 i = 0 ;
 do {
 ch = * src ++ ;
 if ( ! IS_BIDI_CONTROL_CHAR ( ch ) ) {
 ++ i ;
 }
 }
 while ( -- length > 0 ) ;
 src -= srcLength ;
 }
 if ( destSize < i ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return i ;
 }
 destSize = i ;
 do {
 i = srcLength ;
 U16_PREV ( src , 0 , srcLength , c ) ;
 if ( options & UBIDI_KEEP_BASE_COMBINING ) {
 while ( srcLength > 0 && IS_COMBINING ( u_charType ( c ) ) ) {
 U16_PREV ( src , 0 , srcLength , c ) ;
 }
 }
 if ( options & UBIDI_REMOVE_BIDI_CONTROLS && IS_BIDI_CONTROL_CHAR ( c ) ) {
 continue ;
 }
 j = srcLength ;
 if ( options & UBIDI_DO_MIRRORING ) {
 int32_t k = 0 ;
 c = u_charMirror ( c ) ;
 U16_APPEND_UNSAFE ( dest , k , c ) ;
 dest += k ;
 j += k ;
 }
 while ( j < i ) {
 * dest ++ = src [ j ++ ] ;
 }
 }
 while ( srcLength > 0 ) ;
 break ;
 }
 return destSize ;
 }