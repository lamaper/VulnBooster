Oid get_op_opfamily_sortfamily ( Oid opno , Oid opfamily ) {
 HeapTuple tp ;
 Form_pg_amop amop_tup ;
 Oid result ;
 tp = SearchSysCache3 ( AMOPOPID , ObjectIdGetDatum ( opno ) , CharGetDatum ( AMOP_ORDER ) , ObjectIdGetDatum ( opfamily ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) return InvalidOid ;
 amop_tup = ( Form_pg_amop ) GETSTRUCT ( tp ) ;
 result = amop_tup -> amopsortfamily ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }