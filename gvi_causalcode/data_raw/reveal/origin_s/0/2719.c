static UBool action_reverse ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 ubidi_writeReverse ( pTransform -> src , pTransform -> srcLength , pTransform -> dest , pTransform -> destSize , UBIDI_REORDER_DEFAULT , pErrorCode ) ;
 * pTransform -> pDestLength = pTransform -> srcLength ;
 return TRUE ;
 }