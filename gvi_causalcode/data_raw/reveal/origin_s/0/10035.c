Oid get_element_type ( Oid typid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_type typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 Oid result ;
 if ( typtup -> typlen == - 1 ) result = typtup -> typelem ;
 else result = InvalidOid ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }