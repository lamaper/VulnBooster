Oid get_base_element_type ( Oid typid ) {
 for ( ;
 ;
 ) {
 HeapTuple tup ;
 Form_pg_type typTup ;
 tup = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( ! HeapTupleIsValid ( tup ) ) break ;
 typTup = ( Form_pg_type ) GETSTRUCT ( tup ) ;
 if ( typTup -> typtype != TYPTYPE_DOMAIN ) {
 Oid result ;
 if ( typTup -> typlen == - 1 ) result = typTup -> typelem ;
 else result = InvalidOid ;
 ReleaseSysCache ( tup ) ;
 return result ;
 }
 typid = typTup -> typbasetype ;
 ReleaseSysCache ( tup ) ;
 }
 return InvalidOid ;
 }