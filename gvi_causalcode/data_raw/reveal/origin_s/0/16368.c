void get_typlenbyval ( Oid typid , int16 * typlen , bool * typbyval ) {
 HeapTuple tp ;
 Form_pg_type typtup ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for type %u" , typid ) ;
 typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 * typlen = typtup -> typlen ;
 * typbyval = typtup -> typbyval ;
 ReleaseSysCache ( tp ) ;
 }