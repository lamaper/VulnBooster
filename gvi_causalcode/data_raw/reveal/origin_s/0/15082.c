char get_rel_relkind ( Oid relid ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( RELOID , ObjectIdGetDatum ( relid ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_class reltup = ( Form_pg_class ) GETSTRUCT ( tp ) ;
 char result ;
 result = reltup -> relkind ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return '\0' ;
 }