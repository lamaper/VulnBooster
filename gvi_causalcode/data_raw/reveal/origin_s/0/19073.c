static List * expand_function_arguments ( List * args , Oid result_type , HeapTuple func_tuple ) {
 Form_pg_proc funcform = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 bool has_named_args = false ;
 ListCell * lc ;
 foreach ( lc , args ) {
 Node * arg = ( Node * ) lfirst ( lc ) ;
 if ( IsA ( arg , NamedArgExpr ) ) {
 has_named_args = true ;
 break ;
 }
 }
 if ( has_named_args ) {
 args = reorder_function_arguments ( args , func_tuple ) ;
 recheck_cast_function_args ( args , result_type , func_tuple ) ;
 }
 else if ( list_length ( args ) < funcform -> pronargs ) {
 args = add_function_defaults ( args , func_tuple ) ;
 recheck_cast_function_args ( args , result_type , func_tuple ) ;
 }
 return args ;
 }