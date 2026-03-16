void proto_tree_move_item ( proto_tree * tree , proto_item * fixed_item , proto_item * item_to_move ) {
 if ( ! tree || ! PTREE_DATA ( tree ) -> visible ) return ;
 DISSECTOR_ASSERT ( item_to_move -> parent == tree ) ;
 DISSECTOR_ASSERT ( fixed_item -> parent == tree ) ;
 if ( tree -> first_child == item_to_move ) {
 tree -> first_child = item_to_move -> next ;
 DISSECTOR_ASSERT ( tree -> last_child != item_to_move ) ;
 }
 else {
 proto_item * curr_item ;
 for ( curr_item = tree -> first_child ;
 curr_item != NULL ;
 curr_item = curr_item -> next ) {
 if ( curr_item -> next == item_to_move ) {
 break ;
 }
 }
 DISSECTOR_ASSERT ( curr_item ) ;
 curr_item -> next = item_to_move -> next ;
 if ( tree -> last_child == item_to_move ) {
 tree -> last_child = curr_item ;
 }
 }
 item_to_move -> next = fixed_item -> next ;
 fixed_item -> next = item_to_move ;
 if ( tree -> last_child == fixed_item ) {
 tree -> last_child = item_to_move ;
 }
 }