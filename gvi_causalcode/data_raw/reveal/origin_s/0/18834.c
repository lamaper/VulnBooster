static TupleDesc get_cached_rowtype ( Oid type_id , int32 typmod , TupleDesc * cache_field , ExprContext * econtext ) {
 TupleDesc tupDesc = * cache_field ;
 if ( tupDesc == NULL || type_id != tupDesc -> tdtypeid || typmod != tupDesc -> tdtypmod ) {
 tupDesc = lookup_rowtype_tupdesc ( type_id , typmod ) ;
 if ( * cache_field ) {
 ReleaseTupleDesc ( * cache_field ) ;
 }
 else {
 RegisterExprContextCallback ( econtext , ShutdownTupleDescRef , PointerGetDatum ( cache_field ) ) ;
 }
 * cache_field = tupDesc ;
 }
 return tupDesc ;
 }