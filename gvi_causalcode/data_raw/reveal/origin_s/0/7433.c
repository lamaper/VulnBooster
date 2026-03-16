static gboolean proto_tree_traverse_pre_order ( proto_tree * tree , proto_tree_traverse_func func , gpointer data ) {
 proto_node * pnode = tree ;
 proto_node * child ;
 proto_node * current ;
 if ( func ( pnode , data ) ) return TRUE ;
 child = pnode -> first_child ;
 while ( child != NULL ) {
 current = child ;
 child = current -> next ;
 if ( proto_tree_traverse_pre_order ( ( proto_tree * ) current , func , data ) ) return TRUE ;
 }
 return FALSE ;
 }