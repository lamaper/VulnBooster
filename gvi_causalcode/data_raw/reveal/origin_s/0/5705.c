AttrNumber get_attnum ( Oid relid , const char * attname ) {
 HeapTuple tp ;
 tp = SearchSysCacheAttName ( relid , attname ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_attribute att_tup = ( Form_pg_attribute ) GETSTRUCT ( tp ) ;
 AttrNumber result ;
 result = att_tup -> attnum ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidAttrNumber ;
 }