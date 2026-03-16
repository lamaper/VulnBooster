static List * add_function_defaults ( List * args , HeapTuple func_tuple ) {
 Form_pg_proc funcform = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 int nargsprovided = list_length ( args ) ;
 List * defaults ;
 int ndelete ;
 defaults = fetch_function_defaults ( func_tuple ) ;
 ndelete = nargsprovided + list_length ( defaults ) - funcform -> pronargs ;
 if ( ndelete < 0 ) elog ( ERROR , "not enough default arguments" ) ;
 while ( ndelete -- > 0 ) defaults = list_delete_first ( defaults ) ;
 return list_concat ( list_copy ( args ) , defaults ) ;
 }