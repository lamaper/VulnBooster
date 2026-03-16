static int cost_segmap ( int * segcounts , vp9_prob * probs ) {
 const int c01 = segcounts [ 0 ] + segcounts [ 1 ] ;
 const int c23 = segcounts [ 2 ] + segcounts [ 3 ] ;
 const int c45 = segcounts [ 4 ] + segcounts [ 5 ] ;
 const int c67 = segcounts [ 6 ] + segcounts [ 7 ] ;
 const int c0123 = c01 + c23 ;
 const int c4567 = c45 + c67 ;
 int cost = c0123 * vp9_cost_zero ( probs [ 0 ] ) + c4567 * vp9_cost_one ( probs [ 0 ] ) ;
 if ( c0123 > 0 ) {
 cost += c01 * vp9_cost_zero ( probs [ 1 ] ) + c23 * vp9_cost_one ( probs [ 1 ] ) ;
 if ( c01 > 0 ) cost += segcounts [ 0 ] * vp9_cost_zero ( probs [ 3 ] ) + segcounts [ 1 ] * vp9_cost_one ( probs [ 3 ] ) ;
 if ( c23 > 0 ) cost += segcounts [ 2 ] * vp9_cost_zero ( probs [ 4 ] ) + segcounts [ 3 ] * vp9_cost_one ( probs [ 4 ] ) ;
 }
 if ( c4567 > 0 ) {
 cost += c45 * vp9_cost_zero ( probs [ 2 ] ) + c67 * vp9_cost_one ( probs [ 2 ] ) ;
 if ( c45 > 0 ) cost += segcounts [ 4 ] * vp9_cost_zero ( probs [ 5 ] ) + segcounts [ 5 ] * vp9_cost_one ( probs [ 5 ] ) ;
 if ( c67 > 0 ) cost += segcounts [ 6 ] * vp9_cost_zero ( probs [ 6 ] ) + segcounts [ 7 ] * vp9_cost_one ( probs [ 6 ] ) ;
 }
 return cost ;
 }