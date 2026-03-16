static void free_tree_contexts ( PC_TREE * tree ) {
 free_mode_context ( & tree -> none ) ;
 free_mode_context ( & tree -> horizontal [ 0 ] ) ;
 free_mode_context ( & tree -> horizontal [ 1 ] ) ;
 free_mode_context ( & tree -> vertical [ 0 ] ) ;
 free_mode_context ( & tree -> vertical [ 1 ] ) ;
 }