static List * reorder_function_arguments ( List * args , HeapTuple func_tuple ) {
 Form_pg_proc funcform = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 int pronargs = funcform -> pronargs ;
 int nargsprovided = list_length ( args ) ;
 Node * argarray [ FUNC_MAX_ARGS ] ;
 ListCell * lc ;
 int i ;
 Assert ( nargsprovided <= pronargs ) ;
 if ( pronargs > FUNC_MAX_ARGS ) elog ( ERROR , "too many function arguments" ) ;
 MemSet ( argarray , 0 , pronargs * sizeof ( Node * ) ) ;
 i = 0 ;
 foreach ( lc , args ) {
 Node * arg = ( Node * ) lfirst ( lc ) ;
 if ( ! IsA ( arg , NamedArgExpr ) ) {
 Assert ( argarray [ i ] == NULL ) ;
 argarray [ i ++ ] = arg ;
 }
 else {
 NamedArgExpr * na = ( NamedArgExpr * ) arg ;
 Assert ( argarray [ na -> argnumber ] == NULL ) ;
 argarray [ na -> argnumber ] = ( Node * ) na -> arg ;
 }
 }
 if ( nargsprovided < pronargs ) {
 List * defaults = fetch_function_defaults ( func_tuple ) ;
 i = pronargs - funcform -> pronargdefaults ;
 foreach ( lc , defaults ) {
 if ( argarray [ i ] == NULL ) argarray [ i ] = ( Node * ) lfirst ( lc ) ;
 i ++ ;
 }
 }
 args = NIL ;
 for ( i = 0 ;
 i < pronargs ;
 i ++ ) {
 Assert ( argarray [ i ] != NULL ) ;
 args = lappend ( args , argarray [ i ] ) ;
 }
 return args ;
 }