static bool contain_subplans_walker ( Node * node , void * context ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , SubPlan ) || IsA ( node , AlternativeSubPlan ) || IsA ( node , SubLink ) ) return true ;
 return expression_tree_walker ( node , contain_subplans_walker , context ) ;
 }