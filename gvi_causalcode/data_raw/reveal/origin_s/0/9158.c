bool op_mergejoinable ( Oid opno , Oid inputtype ) {
 bool result = false ;
 HeapTuple tp ;
 TypeCacheEntry * typentry ;
 if ( opno == ARRAY_EQ_OP ) {
 typentry = lookup_type_cache ( inputtype , TYPECACHE_CMP_PROC ) ;
 if ( typentry -> cmp_proc == F_BTARRAYCMP ) result = true ;
 }
 else if ( opno == RECORD_EQ_OP ) {
 typentry = lookup_type_cache ( inputtype , TYPECACHE_CMP_PROC ) ;
 if ( typentry -> cmp_proc == F_BTRECORDCMP ) result = true ;
 }
 else {
 tp = SearchSysCache1 ( OPEROID , ObjectIdGetDatum ( opno ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_operator optup = ( Form_pg_operator ) GETSTRUCT ( tp ) ;
 result = optup -> oprcanmerge ;
 ReleaseSysCache ( tp ) ;
 }
 }
 return result ;
 }