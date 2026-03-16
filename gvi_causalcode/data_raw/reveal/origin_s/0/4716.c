char get_typstorage ( Oid typid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_type typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 char result ;
 result = typtup -> typstorage ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return 'p' ;
 }