Oid get_func_namespace ( Oid funcid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_proc functup = ( Form_pg_proc ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = functup -> pronamespace ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }