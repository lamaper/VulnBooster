Oid get_rel_type_id ( Oid relid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( RELOID , ObjectIdGetDatum ( relid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_class reltup = ( Form_pg_class ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = reltup -> reltype ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }