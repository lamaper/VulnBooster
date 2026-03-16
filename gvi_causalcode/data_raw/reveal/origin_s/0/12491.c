Oid get_transform_fromsql ( Oid typid , Oid langid , List * trftypes ) {
 HeapTuple tup ;
 if ( ! list_member_oid ( trftypes , typid ) ) return InvalidOid ;
 tup = SearchSysCache2 ( TRFTYPELANG , typid , langid ) ;
 if ( HeapTupleIsValid ( tup ) ) {
 Oid funcid ;
 funcid = ( ( Form_pg_transform ) GETSTRUCT ( tup ) ) -> trffromsql ;
 ReleaseSysCache ( tup ) ;
 return funcid ;
 }
 else return InvalidOid ;
 }