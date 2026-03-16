Oid get_func_rettype ( Oid funcid ) {
 HeapTuple tp ;
 Oid result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 result = ( ( Form_pg_proc ) GETSTRUCT ( tp ) ) -> prorettype ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }