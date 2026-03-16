static bool contain_volatile_functions_not_nextval_walker ( Node * node , void * context ) {
 if ( node == NULL ) return false ;
 if ( check_functions_in_node ( node , contain_volatile_functions_not_nextval_checker , context ) ) return true ;
 if ( IsA ( node , Query ) ) {
 return query_tree_walker ( ( Query * ) node , contain_volatile_functions_not_nextval_walker , context , 0 ) ;
 }
 return expression_tree_walker ( node , contain_volatile_functions_not_nextval_walker , context ) ;
 }