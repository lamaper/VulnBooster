static UBool action_setInverse ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 ( void ) pErrorCode ;
 ubidi_setInverse ( pTransform -> pBidi , TRUE ) ;
 ubidi_setReorderingMode ( pTransform -> pBidi , UBIDI_REORDER_INVERSE_LIKE_DIRECT ) ;
 return FALSE ;
 }