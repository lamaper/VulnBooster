proto_tree * proto_tree_create_root ( packet_info * pinfo ) {
 proto_node * pnode ;
 pnode = g_slice_new ( proto_tree ) ;
 PROTO_NODE_INIT ( pnode ) ;
 pnode -> parent = NULL ;
 PNODE_FINFO ( pnode ) = NULL ;
 pnode -> tree_data = g_slice_new ( tree_data_t ) ;
 pnode -> tree_data -> pinfo = pinfo ;
 pnode -> tree_data -> interesting_hfids = NULL ;
 pnode -> tree_data -> visible = FALSE ;
 pnode -> tree_data -> fake_protocols = TRUE ;
 pnode -> tree_data -> count = 0 ;
 return ( proto_tree * ) pnode ;
 }