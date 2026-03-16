static void ShutdownTupleDescRef ( Datum arg ) {
 TupleDesc * cache_field = ( TupleDesc * ) DatumGetPointer ( arg ) ;
 if ( * cache_field ) ReleaseTupleDesc ( * cache_field ) ;
 * cache_field = NULL ;
 }