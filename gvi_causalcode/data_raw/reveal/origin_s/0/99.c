int32 get_atttypmod ( Oid relid , AttrNumber attnum ) {
 HeapTuple tp ;
 tp = SearchSysCache2 ( ATTNUM , ObjectIdGetDatum ( relid ) , Int16GetDatum ( attnum ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_attribute att_tup = ( Form_pg_attribute ) GETSTRUCT ( tp ) ;
 int32 result ;
 result = att_tup -> atttypmod ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return - 1 ;
 }