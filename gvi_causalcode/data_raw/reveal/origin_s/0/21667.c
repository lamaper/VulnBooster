char func_volatile ( Oid funcid ) {
 HeapTuple tp ;
 char result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 result = ( ( Form_pg_proc ) GETSTRUCT ( tp ) ) -> provolatile ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }