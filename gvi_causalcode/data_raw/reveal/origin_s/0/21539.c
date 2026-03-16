int16 get_typlen ( Oid typid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_type typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 int16 result ;
 result = typtup -> typlen ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return 0 ;
 }