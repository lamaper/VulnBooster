Oid get_atttype ( Oid relid , AttrNumber attnum ) {
 HeapTuple tp ;
 tp = SearchSysCache2 ( ATTNUM , ObjectIdGetDatum ( relid ) , Int16GetDatum ( attnum ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_attribute att_tup = ( Form_pg_attribute ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = att_tup -> atttypid ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }