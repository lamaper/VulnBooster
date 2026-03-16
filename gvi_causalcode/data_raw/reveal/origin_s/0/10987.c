char * get_func_name ( Oid funcid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_proc functup = ( Form_pg_proc ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( functup -> proname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }