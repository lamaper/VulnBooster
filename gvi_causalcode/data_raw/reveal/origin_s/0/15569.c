static int32_t doWriteForward ( const UChar * src , int32_t srcLength , UChar * dest , int32_t destSize , uint16_t options , UErrorCode * pErrorCode ) {
 switch ( options & ( UBIDI_REMOVE_BIDI_CONTROLS | UBIDI_DO_MIRRORING ) ) {
 case 0 : {
 int32_t length = srcLength ;
 if ( destSize < length ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return srcLength ;
 }
 do {
 * dest ++ = * src ++ ;
 }
 while ( -- length > 0 ) ;
 return srcLength ;
 }
 case UBIDI_DO_MIRRORING : {
 int32_t i = 0 , j = 0 ;
 UChar32 c ;
 if ( destSize < srcLength ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return srcLength ;
 }
 do {
 U16_NEXT ( src , i , srcLength , c ) ;
 c = u_charMirror ( c ) ;
 U16_APPEND_UNSAFE ( dest , j , c ) ;
 }
 while ( i < srcLength ) ;
 return srcLength ;
 }
 case UBIDI_REMOVE_BIDI_CONTROLS : {
 int32_t remaining = destSize ;
 UChar c ;
 do {
 c = * src ++ ;
 if ( ! IS_BIDI_CONTROL_CHAR ( c ) ) {
 if ( -- remaining < 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 while ( -- srcLength > 0 ) {
 c = * src ++ ;
 if ( ! IS_BIDI_CONTROL_CHAR ( c ) ) {
 -- remaining ;
 }
 }
 return destSize - remaining ;
 }
 * dest ++ = c ;
 }
 }
 while ( -- srcLength > 0 ) ;
 return destSize - remaining ;
 }
 default : {
 int32_t remaining = destSize ;
 int32_t i , j = 0 ;
 UChar32 c ;
 do {
 i = 0 ;
 U16_NEXT ( src , i , srcLength , c ) ;
 src += i ;
 srcLength -= i ;
 if ( ! IS_BIDI_CONTROL_CHAR ( c ) ) {
 remaining -= i ;
 if ( remaining < 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 while ( srcLength > 0 ) {
 c = * src ++ ;
 if ( ! IS_BIDI_CONTROL_CHAR ( c ) ) {
 -- remaining ;
 }
 -- srcLength ;
 }
 return destSize - remaining ;
 }
 c = u_charMirror ( c ) ;
 U16_APPEND_UNSAFE ( dest , j , c ) ;
 }
 }
 while ( srcLength > 0 ) ;
 return j ;
 }
 }
 }