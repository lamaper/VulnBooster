static const ReorderingScheme * findMatchingScheme ( UBiDiLevel inLevel , UBiDiLevel outLevel , UBiDiOrder inOrder , UBiDiOrder outOrder ) {
 uint32_t i ;
 for ( i = 0 ;
 i < nSchemes ;
 i ++ ) {
 const ReorderingScheme * pScheme = Schemes + i ;
 if ( inLevel == pScheme -> inLevel && outLevel == pScheme -> outLevel && inOrder == pScheme -> inOrder && outOrder == pScheme -> outOrder ) {
 return pScheme ;
 }
 }
 return NULL ;
 }