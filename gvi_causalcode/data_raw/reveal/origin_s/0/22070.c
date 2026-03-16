void proto_tree_reset ( proto_tree * tree ) {
 tree_data_t * tree_data = PTREE_DATA ( tree ) ;
 proto_tree_children_foreach ( tree , proto_tree_free_node , NULL ) ;
 if ( tree_data -> interesting_hfids ) {
 g_hash_table_foreach ( tree_data -> interesting_hfids , free_GPtrArray_value , NULL ) ;
 g_hash_table_remove_all ( tree_data -> interesting_hfids ) ;
 }
 tree_data -> count = 0 ;
 PROTO_NODE_INIT ( tree ) ;
 }