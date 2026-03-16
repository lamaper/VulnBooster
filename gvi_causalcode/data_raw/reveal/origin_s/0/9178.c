bool op_hashjoinable ( Oid opno , Oid inputtype ) {
 bool result = false ;
 HeapTuple tp ;
 TypeCacheEntry * typentry ;
 if ( opno == ARRAY_EQ_OP ) {
 typentry = lookup_type_cache ( inputtype , TYPECACHE_HASH_PROC ) ;
 if ( typentry -> hash_proc == F_HASH_ARRAY ) result = true ;
 }
 else {
 tp = SearchSysCache1 ( OPEROID , ObjectIdGetDatum ( opno ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_operator optup = ( Form_pg_operator ) GETSTRUCT ( tp ) ;
 result = optup -> oprcanhash ;
 ReleaseSysCache ( tp ) ;
 }
 }
 return result ;
 }