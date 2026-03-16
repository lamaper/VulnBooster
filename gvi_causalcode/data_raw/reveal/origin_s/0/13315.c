bool func_strict ( Oid funcid ) {
 HeapTuple tp ;
 bool result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 result = ( ( Form_pg_proc ) GETSTRUCT ( tp ) ) -> proisstrict ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }