char get_rel_persistence ( Oid relid ) {
 HeapTuple tp ;
 Form_pg_class reltup ;
 char result ;
 tp = SearchSysCache1 ( RELOID , ObjectIdGetDatum ( relid ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for relation %u" , relid ) ;
 reltup = ( Form_pg_class ) GETSTRUCT ( tp ) ;
 result = reltup -> relpersistence ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }