static void recheck_cast_function_args ( List * args , Oid result_type , HeapTuple func_tuple ) {
 Form_pg_proc funcform = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 int nargs ;
 Oid actual_arg_types [ FUNC_MAX_ARGS ] ;
 Oid declared_arg_types [ FUNC_MAX_ARGS ] ;
 Oid rettype ;
 ListCell * lc ;
 if ( list_length ( args ) > FUNC_MAX_ARGS ) elog ( ERROR , "too many function arguments" ) ;
 nargs = 0 ;
 foreach ( lc , args ) {
 actual_arg_types [ nargs ++ ] = exprType ( ( Node * ) lfirst ( lc ) ) ;
 }
 Assert ( nargs == funcform -> pronargs ) ;
 memcpy ( declared_arg_types , funcform -> proargtypes . values , funcform -> pronargs * sizeof ( Oid ) ) ;
 rettype = enforce_generic_type_consistency ( actual_arg_types , declared_arg_types , nargs , funcform -> prorettype , false ) ;
 if ( rettype != result_type ) elog ( ERROR , "function's resolved result type changed during planning" ) ;
 make_fn_arguments ( NULL , args , actual_arg_types , declared_arg_types ) ;
 }