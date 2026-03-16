void get_type_category_preferred ( Oid typid , char * typcategory , bool * typispreferred ) {
 HeapTuple tp ;
 Form_pg_type typtup ;
 tp = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for type %u" , typid ) ;
 typtup = ( Form_pg_type ) GETSTRUCT ( tp ) ;
 * typcategory = typtup -> typcategory ;
 * typispreferred = typtup -> typispreferred ;
 ReleaseSysCache ( tp ) ;
 }