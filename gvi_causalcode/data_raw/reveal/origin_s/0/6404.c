gboolean proto_tree_traverse_post_order ( proto_tree * tree , proto_tree_traverse_func func , gpointer data ) {
 proto_node * pnode = tree ;
 proto_node * child ;
 proto_node * current ;
 child = pnode -> first_child ;
 while ( child != NULL ) {
 current = child ;
 child = current -> next ;
 if ( proto_tree_traverse_post_order ( ( proto_tree * ) current , func , data ) ) return TRUE ;
 }
 if ( func ( pnode , data ) ) return TRUE ;
 return FALSE ;
 }