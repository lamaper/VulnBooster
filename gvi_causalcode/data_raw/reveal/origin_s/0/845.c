static UBool action_shapeArabic ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 if ( ( pTransform -> letters | pTransform -> digits ) == 0 ) {
 return FALSE ;
 }
 if ( pTransform -> pActiveScheme -> lettersDir == pTransform -> pActiveScheme -> digitsDir ) {
 doShape ( pTransform , pTransform -> letters | pTransform -> digits | pTransform -> pActiveScheme -> lettersDir , pErrorCode ) ;
 }
 else {
 doShape ( pTransform , pTransform -> digits | pTransform -> pActiveScheme -> digitsDir , pErrorCode ) ;
 if ( U_SUCCESS ( * pErrorCode ) ) {
 updateSrc ( pTransform , pTransform -> dest , * pTransform -> pDestLength , * pTransform -> pDestLength , pErrorCode ) ;
 doShape ( pTransform , pTransform -> letters | pTransform -> pActiveScheme -> lettersDir , pErrorCode ) ;
 }
 }
 return TRUE ;
 }