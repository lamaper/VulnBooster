static void prob_diff_update ( const vp9_tree_index * tree , vp9_prob probs [ ] , const unsigned int counts [ ] , int n , vp9_writer * w ) {
 int i ;
 unsigned int branch_ct [ 32 ] [ 2 ] ;
 assert ( n <= 32 ) ;
 vp9_tree_probs_from_distribution ( tree , branch_ct , counts ) ;
 for ( i = 0 ;
 i < n - 1 ;
 ++ i ) vp9_cond_prob_diff_update ( w , & probs [ i ] , branch_ct [ i ] ) ;
 }