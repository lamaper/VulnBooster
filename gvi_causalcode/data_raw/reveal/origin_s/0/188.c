static UBool action_reorder ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 ubidi_writeReordered ( pTransform -> pBidi , pTransform -> dest , pTransform -> destSize , pTransform -> reorderingOptions , pErrorCode ) ;
 * pTransform -> pDestLength = pTransform -> srcLength ;
 pTransform -> reorderingOptions = UBIDI_REORDER_DEFAULT ;
 return TRUE ;
 }