static void calc_segtree_probs ( int * segcounts , vp9_prob * segment_tree_probs ) {
 const int c01 = segcounts [ 0 ] + segcounts [ 1 ] ;
 const int c23 = segcounts [ 2 ] + segcounts [ 3 ] ;
 const int c45 = segcounts [ 4 ] + segcounts [ 5 ] ;
 const int c67 = segcounts [ 6 ] + segcounts [ 7 ] ;
 segment_tree_probs [ 0 ] = get_binary_prob ( c01 + c23 , c45 + c67 ) ;
 segment_tree_probs [ 1 ] = get_binary_prob ( c01 , c23 ) ;
 segment_tree_probs [ 2 ] = get_binary_prob ( c45 , c67 ) ;
 segment_tree_probs [ 3 ] = get_binary_prob ( segcounts [ 0 ] , segcounts [ 1 ] ) ;
 segment_tree_probs [ 4 ] = get_binary_prob ( segcounts [ 2 ] , segcounts [ 3 ] ) ;
 segment_tree_probs [ 5 ] = get_binary_prob ( segcounts [ 4 ] , segcounts [ 5 ] ) ;
 segment_tree_probs [ 6 ] = get_binary_prob ( segcounts [ 6 ] , segcounts [ 7 ] ) ;
 }