void get_atttypetypmodcoll ( Oid relid , AttrNumber attnum , Oid * typid , int32 * typmod , Oid * collid ) {
 HeapTuple tp ;
 Form_pg_attribute att_tup ;
 tp = SearchSysCache2 ( ATTNUM , ObjectIdGetDatum ( relid ) , Int16GetDatum ( attnum ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for attribute %d of relation %u" , attnum , relid ) ;
 att_tup = ( Form_pg_attribute ) GETSTRUCT ( tp ) ;
 * typid = att_tup -> atttypid ;
 * typmod = att_tup -> atttypmod ;
 * collid = att_tup -> attcollation ;
 ReleaseSysCache ( tp ) ;
 }