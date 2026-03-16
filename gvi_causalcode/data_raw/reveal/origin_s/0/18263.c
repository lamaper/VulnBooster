static Node * substitute_actual_parameters_mutator ( Node * node , substitute_actual_parameters_context * context ) {
 if ( node == NULL ) return NULL ;
 if ( IsA ( node , Param ) ) {
 Param * param = ( Param * ) node ;
 if ( param -> paramkind != PARAM_EXTERN ) elog ( ERROR , "unexpected paramkind: %d" , ( int ) param -> paramkind ) ;
 if ( param -> paramid <= 0 || param -> paramid > context -> nargs ) elog ( ERROR , "invalid paramid: %d" , param -> paramid ) ;
 context -> usecounts [ param -> paramid - 1 ] ++ ;
 return list_nth ( context -> args , param -> paramid - 1 ) ;
 }
 return expression_tree_mutator ( node , substitute_actual_parameters_mutator , ( void * ) context ) ;
 }