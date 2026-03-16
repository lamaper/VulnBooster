char * get_opname ( Oid opno ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( OPEROID , ObjectIdGetDatum ( opno ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_operator optup = ( Form_pg_operator ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( optup -> oprname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }