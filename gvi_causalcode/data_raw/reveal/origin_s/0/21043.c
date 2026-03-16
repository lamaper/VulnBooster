static void alloc_tree_contexts ( VP9_COMMON * cm , PC_TREE * tree , int num_4x4_blk ) {
 alloc_mode_context ( cm , num_4x4_blk , & tree -> none ) ;
 alloc_mode_context ( cm , num_4x4_blk / 2 , & tree -> horizontal [ 0 ] ) ;
 alloc_mode_context ( cm , num_4x4_blk / 2 , & tree -> vertical [ 0 ] ) ;
 alloc_mode_context ( cm , num_4x4_blk / 2 , & tree -> horizontal [ 1 ] ) ;
 alloc_mode_context ( cm , num_4x4_blk / 2 , & tree -> vertical [ 1 ] ) ;
 }