Oid get_typ_typrelid ( Oid typid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_type typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = typtup -> typrelid ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }