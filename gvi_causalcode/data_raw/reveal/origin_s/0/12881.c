static void getSingleRun ( UBiDi * pBiDi , UBiDiLevel level ) {
 pBiDi -> runs = pBiDi -> simpleRuns ;
 pBiDi -> runCount = 1 ;
 pBiDi -> runs [ 0 ] . logicalStart = MAKE_INDEX_ODD_PAIR ( 0 , level ) ;
 pBiDi -> runs [ 0 ] . visualLimit = pBiDi -> length ;
 pBiDi -> runs [ 0 ] . insertRemove = 0 ;
 }