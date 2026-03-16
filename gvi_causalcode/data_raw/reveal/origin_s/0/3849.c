int get_op_opfamily_strategy ( Oid opno , Oid opfamily ) {
 HeapTuple tp ;
 Form_pg_amop amop_tup ;
 int result ;
 tp = SearchSysCache3 ( AMOPOPID , ObjectIdGetDatum ( opno ) , CharGetDatum ( AMOP_SEARCH ) , ObjectIdGetDatum ( opfamily ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) return 0 ;
 amop_tup = ( Form_pg_amop ) GETSTRUCT ( tp ) ;
 result = amop_tup -> amopstrategy ;
 ReleaseSysCache ( tp ) ;
 return result ;
 }