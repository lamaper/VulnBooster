static void reorderLine ( UBiDi * pBiDi , UBiDiLevel minLevel , UBiDiLevel maxLevel ) {
 Run * runs , tempRun ;
 UBiDiLevel * levels ;
 int32_t firstRun , endRun , limitRun , runCount ;
 if ( maxLevel <= ( minLevel | 1 ) ) {
 return ;
 }
 ++ minLevel ;
 runs = pBiDi -> runs ;
 levels = pBiDi -> levels ;
 runCount = pBiDi -> runCount ;
 if ( pBiDi -> trailingWSStart < pBiDi -> length ) {
 -- runCount ;
 }
 while ( -- maxLevel >= minLevel ) {
 firstRun = 0 ;
 for ( ;
 ;
 ) {
 while ( firstRun < runCount && levels [ runs [ firstRun ] . logicalStart ] < maxLevel ) {
 ++ firstRun ;
 }
 if ( firstRun >= runCount ) {
 break ;
 }
 for ( limitRun = firstRun ;
 ++ limitRun < runCount && levels [ runs [ limitRun ] . logicalStart ] >= maxLevel ;
 ) {
 }
 endRun = limitRun - 1 ;
 while ( firstRun < endRun ) {
 tempRun = runs [ firstRun ] ;
 runs [ firstRun ] = runs [ endRun ] ;
 runs [ endRun ] = tempRun ;
 ++ firstRun ;
 -- endRun ;
 }
 if ( limitRun == runCount ) {
 break ;
 }
 else {
 firstRun = limitRun + 1 ;
 }
 }
 }
 if ( ! ( minLevel & 1 ) ) {
 firstRun = 0 ;
 if ( pBiDi -> trailingWSStart == pBiDi -> length ) {
 -- runCount ;
 }
 while ( firstRun < runCount ) {
 tempRun = runs [ firstRun ] ;
 runs [ firstRun ] = runs [ runCount ] ;
 runs [ runCount ] = tempRun ;
 ++ firstRun ;
 -- runCount ;
 }
 }
 }