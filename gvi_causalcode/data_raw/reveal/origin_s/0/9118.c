static int index_mb ( uint8_t cluster [ ] , uint8_t cb [ ] , int numCB , int * outIndex , int dim ) {
 int i , lDiff = INT_MAX , pick = 0 ;
 for ( i = 0 ;
 i < numCB ;
 i ++ ) {
 int diff = squared_diff_macroblock ( cluster , cb + i * dim * dim * 3 , dim ) ;
 if ( diff < lDiff ) {
 lDiff = diff ;
 pick = i ;
 }
 }
 * outIndex = pick ;
 return lDiff ;
 }