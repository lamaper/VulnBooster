bool get_typisdefined ( Oid typid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_type typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 bool result ;
 result = typtup -> typisdefined ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return false ;
 }