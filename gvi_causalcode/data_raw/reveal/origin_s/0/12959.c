char * get_namespace_name ( Oid nspid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( NAMESPACEOID , ObjectIdGetDatum ( nspid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_namespace nsptup = ( Form_pg_namespace ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( nsptup -> nspname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return NULL ;
 }