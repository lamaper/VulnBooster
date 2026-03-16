char * get_attname ( Oid relid , AttrNumber attnum ) {
 HeapTuple tp ;
 tp = SearchSysCache2 ( ATTNUM , ObjectIdGetDatum ( relid ) , Int16GetDatum ( attnum ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_attribute att_tup = ( Form_pg_attribute ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( att_tup -> attname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }