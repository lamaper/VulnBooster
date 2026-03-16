void proto_register_subtree_array ( gint * const * indices , const int num_indices ) {
 int i ;
 gint * const * ptr = indices ;
 if ( tree_is_expanded != NULL ) {
 tree_is_expanded = ( guint32 * ) g_realloc ( tree_is_expanded , ( 1 + ( ( num_tree_types + num_indices ) / 32 ) ) * sizeof ( guint32 ) ) ;
 for ( i = num_tree_types ;
 i < num_tree_types + num_indices ;
 i ++ ) tree_is_expanded [ i >> 5 ] &= ~ ( 1U << ( i & 31 ) ) ;
 }
 for ( i = 0 ;
 i < num_indices ;
 i ++ , ptr ++ , num_tree_types ++ ) {
 if ( * * ptr != - 1 ) {
 g_error ( "register_subtree_array: subtree item type (ett_...) not -1 !" " This is a development error:" " Either the subtree item type has already been assigned or" " was not initialized to -1." ) ;
 }
 * * ptr = num_tree_types ;
 }
 }