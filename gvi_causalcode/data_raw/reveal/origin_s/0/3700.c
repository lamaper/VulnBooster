gboolean tree_expanded ( int tree_type ) {
 g_assert ( tree_type >= 0 && tree_type < num_tree_types ) ;
 return tree_is_expanded [ tree_type >> 5 ] & ( 1U << ( tree_type & 31 ) ) ;
 }