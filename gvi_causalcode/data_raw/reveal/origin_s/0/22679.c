static UBool action_mirror ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 UChar32 c ;
 uint32_t i = 0 , j = 0 ;
 if ( 0 == ( pTransform -> reorderingOptions & UBIDI_DO_MIRRORING ) ) {
 return FALSE ;
 }
 if ( pTransform -> destSize < pTransform -> srcLength ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return FALSE ;
 }
 do {
 UBool isOdd = ubidi_getLevelAt ( pTransform -> pBidi , i ) & 1 ;
 U16_NEXT ( pTransform -> src , i , pTransform -> srcLength , c ) ;
 U16_APPEND_UNSAFE ( pTransform -> dest , j , isOdd ? u_charMirror ( c ) : c ) ;
 }
 while ( i < pTransform -> srcLength ) ;
 * pTransform -> pDestLength = pTransform -> srcLength ;
 pTransform -> reorderingOptions = UBIDI_REORDER_DEFAULT ;
 return TRUE ;
 }