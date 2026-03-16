void op_input_types ( Oid opno , Oid * lefttype , Oid * righttype ) {
 HeapTuple tp ;
 Form_pg_operator optup ;
 tp = SearchSysCache1 ( OPEROID , ObjectIdGetDatum ( opno ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "cache lookup failed for operator %u" , opno ) ;
 optup = ( Form_pg_operator ) GETSTRUCT ( tp ) ;
 * lefttype = optup -> oprleft ;
 * righttype = optup -> oprright ;
 ReleaseSysCache ( tp ) ;
 }