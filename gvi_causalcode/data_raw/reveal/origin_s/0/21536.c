Oid get_typcollation ( Oid typid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_type typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = typtup -> typcollation ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }