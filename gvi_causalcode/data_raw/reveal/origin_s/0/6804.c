Oid get_array_type ( Oid typid ) {
 HeapTuple tp ;
 Oid result = InvalidOid ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 result = ( ( Form_pg_type ) GETSTRUCT ( tp ) ) -> typarray ;
 ReleaseSysCache ( tp ) ;
 }
 return result ;
 }