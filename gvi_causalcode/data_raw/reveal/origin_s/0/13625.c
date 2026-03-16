static int element_compare ( const void * key1 , const void * key2 , void * arg ) {
 Datum d1 = * ( ( const Datum * ) key1 ) ;
 Datum d2 = * ( ( const Datum * ) key2 ) ;
 FmgrInfo * cmpfunc = ( FmgrInfo * ) arg ;
 Datum c ;
 c = FunctionCall2Coll ( cmpfunc , DEFAULT_COLLATION_OID , d1 , d2 ) ;
 return DatumGetInt32 ( c ) ;
 }