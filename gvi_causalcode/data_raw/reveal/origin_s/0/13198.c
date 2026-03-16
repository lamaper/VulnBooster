Oid get_rel_tablespace ( Oid relid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( RELOID , ObjectIdGetDatum ( relid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_class reltup = ( Form_pg_class ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = reltup -> reltablespace ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }