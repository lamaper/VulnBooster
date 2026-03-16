proto_tree * proto_tree_get_parent_tree ( proto_tree * tree ) {
 if ( ! tree ) return NULL ;
 if ( ! tree -> parent ) return tree ;
 return ( proto_tree * ) tree -> parent ;
 }