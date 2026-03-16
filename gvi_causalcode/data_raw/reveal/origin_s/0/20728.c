void vp9_setup_pc_tree ( VP9_COMMON * cm , VP9_COMP * cpi ) {
 int i , j ;
 const int leaf_nodes = 64 ;
 const int tree_nodes = 64 + 16 + 4 + 1 ;
 int pc_tree_index = 0 ;
 PC_TREE * this_pc ;
 PICK_MODE_CONTEXT * this_leaf ;
 int square_index = 1 ;
 int nodes ;
 vpx_free ( cpi -> leaf_tree ) ;
 CHECK_MEM_ERROR ( cm , cpi -> leaf_tree , vpx_calloc ( leaf_nodes , sizeof ( * cpi -> leaf_tree ) ) ) ;
 vpx_free ( cpi -> pc_tree ) ;
 CHECK_MEM_ERROR ( cm , cpi -> pc_tree , vpx_calloc ( tree_nodes , sizeof ( * cpi -> pc_tree ) ) ) ;
 this_pc = & cpi -> pc_tree [ 0 ] ;
 this_leaf = & cpi -> leaf_tree [ 0 ] ;
 for ( i = 0 ;
 i < leaf_nodes ;
 ++ i ) alloc_mode_context ( cm , 1 , & cpi -> leaf_tree [ i ] ) ;
 for ( pc_tree_index = 0 ;
 pc_tree_index < leaf_nodes ;
 ++ pc_tree_index ) {
 PC_TREE * const tree = & cpi -> pc_tree [ pc_tree_index ] ;
 tree -> block_size = square [ 0 ] ;
 alloc_tree_contexts ( cm , tree , 4 ) ;
 tree -> leaf_split [ 0 ] = this_leaf ++ ;
 for ( j = 1 ;
 j < 4 ;
 j ++ ) tree -> leaf_split [ j ] = tree -> leaf_split [ 0 ] ;
 }
 for ( nodes = 16 ;
 nodes > 0 ;
 nodes >>= 2 ) {
 for ( i = 0 ;
 i < nodes ;
 ++ i ) {
 PC_TREE * const tree = & cpi -> pc_tree [ pc_tree_index ] ;
 alloc_tree_contexts ( cm , tree , 4 << ( 2 * square_index ) ) ;
 tree -> block_size = square [ square_index ] ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) tree -> split [ j ] = this_pc ++ ;
 ++ pc_tree_index ;
 }
 ++ square_index ;
 }
 cpi -> pc_root = & cpi -> pc_tree [ tree_nodes - 1 ] ;
 cpi -> pc_root [ 0 ] . none . best_mode_index = 2 ;
 }