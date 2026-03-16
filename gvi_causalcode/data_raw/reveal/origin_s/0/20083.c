static bool has_parallel_hazard_walker ( Node * node , has_parallel_hazard_arg * context ) {
 if ( node == NULL ) return false ;
 if ( check_functions_in_node ( node , has_parallel_hazard_checker , context ) ) return true ;
 if ( IsA ( node , CoerceToDomain ) ) {
 if ( ! context -> allow_restricted ) return true ;
 }
 else if ( IsA ( node , RestrictInfo ) ) {
 RestrictInfo * rinfo = ( RestrictInfo * ) node ;
 return has_parallel_hazard_walker ( ( Node * ) rinfo -> clause , context ) ;
 }
 else if ( IsA ( node , SubLink ) || IsA ( node , SubPlan ) || IsA ( node , AlternativeSubPlan ) ) {
 if ( ! context -> allow_restricted ) return true ;
 }
 else if ( IsA ( node , Param ) ) {
 if ( ! context -> allow_restricted ) return true ;
 }
 else if ( IsA ( node , Query ) ) {
 Query * query = ( Query * ) node ;
 if ( query -> rowMarks != NULL ) return true ;
 return query_tree_walker ( query , has_parallel_hazard_walker , context , 0 ) ;
 }
 return expression_tree_walker ( node , has_parallel_hazard_walker , context ) ;
 }