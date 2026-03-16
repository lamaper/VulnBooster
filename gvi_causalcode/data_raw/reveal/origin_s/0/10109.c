void vp9_free_pc_tree ( VP9_COMP * cpi ) {
 const int tree_nodes = 64 + 16 + 4 + 1 ;
 int i ;
 for ( i = 0 ;
 i < 64 ;
 ++ i ) free_mode_context ( & cpi -> leaf_tree [ i ] ) ;
 for ( i = 0 ;
 i < tree_nodes ;
 ++ i ) free_tree_contexts ( & cpi -> pc_tree [ i ] ) ;
 vpx_free ( cpi -> pc_tree ) ;
 cpi -> pc_tree = NULL ;
 vpx_free ( cpi -> leaf_tree ) ;
 cpi -> leaf_tree = NULL ;
 }