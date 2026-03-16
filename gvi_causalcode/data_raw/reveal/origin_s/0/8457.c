float4 get_func_cost ( Oid funcid ) {
 HeapTuple tp ;
 float4 result ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 result = ( ( Form_pg_proc ) GETSTRUCT ( tp ) ) -> procost ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }