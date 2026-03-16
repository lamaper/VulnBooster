static bool rowtype_field_matches ( Oid rowtypeid , int fieldnum , Oid expectedtype , int32 expectedtypmod , Oid expectedcollation ) {
 TupleDesc tupdesc ;
 Form_pg_attribute attr ;
 if ( rowtypeid == RECORDOID ) return true ;
 tupdesc = lookup_rowtype_tupdesc ( rowtypeid , - 1 ) ;
 if ( fieldnum <= 0 || fieldnum > tupdesc -> natts ) {
 ReleaseTupleDesc ( tupdesc ) ;
 return false ;
 }
 attr = tupdesc -> attrs [ fieldnum - 1 ] ;
 if ( attr -> attisdropped || attr -> atttypid != expectedtype || attr -> atttypmod != expectedtypmod || attr -> attcollation != expectedcollation ) {
 ReleaseTupleDesc ( tupdesc ) ;
 return false ;
 }
 ReleaseTupleDesc ( tupdesc ) ;
 return true ;
 }