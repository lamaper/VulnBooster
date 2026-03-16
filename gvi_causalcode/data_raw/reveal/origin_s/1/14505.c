static UBool action_setRunsOnly ( UBiDiTransform * pTransform , UErrorCode * pErrorCode ) {
 ubidi_setReorderingMode ( pTransform -> pBidi , UBIDI_REORDER_RUNS_ONLY ) ;
 return FALSE ;
 }