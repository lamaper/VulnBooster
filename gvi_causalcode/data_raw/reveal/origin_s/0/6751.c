Oid getBaseTypeAndTypmod ( Oid typid , int32 * typmod ) {
 for ( ;
 ;
 ) {
 HeapTuple tup ;
 Form_pg_type typTup ;
 tup = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( ! HeapTupleIsValid ( tup ) ) elog ( ERROR , "cache lookup failed for type %u" , typid ) ;
 typTup = ( Form_pg_type ) GETSTRUCT ( tup ) ;
 if ( typTup -> typtype != TYPTYPE_DOMAIN ) {
 ReleaseSysCache ( tup ) ;
 break ;
 }
 Assert ( * typmod == - 1 ) ;
 typid = typTup -> typbasetype ;
 * typmod = typTup -> typtypmod ;
 ReleaseSysCache ( tup ) ;
 }
 return typid ;
 }