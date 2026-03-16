static Node * substitute_actual_srf_parameters_mutator ( Node * node , substitute_actual_srf_parameters_context * context ) {
 Node * result ;
 if ( node == NULL ) return NULL ;
 if ( IsA ( node , Query ) ) {
 context -> sublevels_up ++ ;
 result = ( Node * ) query_tree_mutator ( ( Query * ) node , substitute_actual_srf_parameters_mutator , ( void * ) context , 0 ) ;
 context -> sublevels_up -- ;
 return result ;
 }
 if ( IsA ( node , Param ) ) {
 Param * param = ( Param * ) node ;
 if ( param -> paramkind == PARAM_EXTERN ) {
 if ( param -> paramid <= 0 || param -> paramid > context -> nargs ) elog ( ERROR , "invalid paramid: %d" , param -> paramid ) ;
 result = copyObject ( list_nth ( context -> args , param -> paramid - 1 ) ) ;
 IncrementVarSublevelsUp ( result , context -> sublevels_up , 0 ) ;
 return result ;
 }
 }
 return expression_tree_mutator ( node , substitute_actual_srf_parameters_mutator , ( void * ) context ) ;
 }