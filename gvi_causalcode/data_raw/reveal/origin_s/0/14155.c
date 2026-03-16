Oid get_op_rettype ( Oid opno ) {
 HeapTuple tp ;
 tp = SearchSysCache1 ( OPEROID , ObjectIdGetDatum ( opno ) ) ;
 if ( HeapTupleIsValid ( tp ) ) {
 Form_pg_operator optup = ( Form_pg_operator ) GETSTRUCT ( tp ) ;
 Oid result ;
 result = optup -> oprresult ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }
 else return InvalidOid ;
 }