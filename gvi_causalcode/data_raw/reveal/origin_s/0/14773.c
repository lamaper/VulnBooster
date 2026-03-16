char * get_rel_name ( Oid relid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( RELOID , ObjectIdGetDatum ( relid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_class reltup = ( Form_pg_class ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( reltup -> relname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }