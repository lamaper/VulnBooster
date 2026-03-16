static void remap_codebooks ( RoqContext * enc , RoqTempdata * tempData ) {
 int i , j , idx = 0 ;
 for ( i = 0 ;
 i < MAX_CBS_4x4 ;
 i ++ ) {
 if ( tempData -> codebooks . usedCB4 [ i ] ) {
 tempData -> i2f4 [ i ] = idx ;
 tempData -> f2i4 [ idx ] = i ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) tempData -> codebooks . usedCB2 [ enc -> cb4x4 [ i ] . idx [ j ] ] ++ ;
 idx ++ ;
 }
 }
 tempData -> numCB4 = idx ;
 idx = 0 ;
 for ( i = 0 ;
 i < MAX_CBS_2x2 ;
 i ++ ) {
 if ( tempData -> codebooks . usedCB2 [ i ] ) {
 tempData -> i2f2 [ i ] = idx ;
 tempData -> f2i2 [ idx ] = i ;
 idx ++ ;
 }
 }
 tempData -> numCB2 = idx ;
 }