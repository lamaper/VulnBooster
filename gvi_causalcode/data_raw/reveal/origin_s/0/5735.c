Oid get_opclass_input_type ( Oid opclass ) {
 HeapTuple tp ;
 Form_pg_opclass cla_tup ;
 Oid result ;
 tp = SearchSysCache1 ( CLAOID , ObjectIdGetDatum ( opclass ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for opclass %u" , opclass ) ;
 cla_tup = ( Form_pg_opclass ) GETSTRUCT ( tp ) ;
 result = cla_tup -> opcintype ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }