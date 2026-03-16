Oid get_transform_tosql ( Oid typid , Oid langid , List * trftypes ) {
 HeapTuple tup ;
 if ( ! list_member_oid ( trftypes , typid ) ) return InvalidOid ;
 tup = SearchSysCache2 ( TRFTYPELANG , typid , langid ) ;
 if ( HeapTupleIsValid ( tup ) ) {
 Oid funcid ;
 funcid = ( ( Form_pg_transform ) GETSTRUCT ( tup ) ) -> trftosql ;
 ReleaseSysCache ( tup ) ;
 return funcid ;
 }
 else return InvalidOid ;
 }