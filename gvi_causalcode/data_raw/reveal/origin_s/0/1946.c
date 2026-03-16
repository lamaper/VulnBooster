static UBool action_resolve ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 ubidi_setPara ( pTransform -> pBidi , pTransform -> src , pTransform -> srcLength , pTransform -> pActiveScheme -> baseLevel , NULL , pErrorCode ) ;
 return FALSE ;
 }