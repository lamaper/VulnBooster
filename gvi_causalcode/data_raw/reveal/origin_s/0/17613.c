float4 get_func_rows ( Oid funcid ) {
 HeapTuple tp ;
 float4 result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 result = ( ( Form_pg_proc ) GETSTRUCT ( tp ) ) -> prorows ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }