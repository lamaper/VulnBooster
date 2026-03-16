Oid get_func_signature ( Oid funcid , Oid * * argtypes , int * nargs ) {
 HeapTuple tp ;
 Form_pg_proc procstruct ;
 Oid result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 procstruct = ( Form_pg_proc ) GETSTRUCT ( tp ) ;
 result = procstruct -> prorettype ;
 * nargs = ( int ) procstruct -> pronargs ;
 Assert ( * nargs == procstruct -> proargtypes . dim1 ) ;
 * argtypes = ( Oid * ) palloc ( * nargs * sizeof ( Oid ) ) ;
 memcpy ( * argtypes , procstruct -> proargtypes . values , * nargs * sizeof ( Oid ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }