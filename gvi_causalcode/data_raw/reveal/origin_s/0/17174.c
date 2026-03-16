char * get_language_name ( Oid langoid , bool missing_ok ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( LANGOID , ObjectIdGetDatum ( langoid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_language lantup = ( Form_pg_language ) GETSTRUCT ( tp ) ;
 char * result ;
 result = pstrdup ( NameStr ( lantup -> lanname ) ) ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 if ( ! missing_ok ) elog ( ERROR , "cache lookup failed for language %u" , langoid ) ;
 return NULL ;
 }