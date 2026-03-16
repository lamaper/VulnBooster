int get_func_nargs ( Oid funcid ) {
 HeapTuple tp ;
 int result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 result = ( ( Form_pg_proc ) GETSTRUCT ( tp ) ) -> pronargs ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }