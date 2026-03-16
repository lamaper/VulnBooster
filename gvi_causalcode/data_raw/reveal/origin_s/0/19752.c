void get_op_opfamily_properties ( Oid opno , Oid opfamily , bool ordering_op , int * strategy , Oid * lefttype , Oid * righttype ) {
 HeapTuple tp ;
 Form_pg_amop amop_tup ;
 tp = SearchSysCache3 ( AMOPOPID , ObjectIdGetDatum ( opno ) , CharGetDatum ( ordering_op ? AMOP_ORDER : AMOP_SEARCH ) , ObjectIdGetDatum ( opfamily ) ) ;
 if ( ! HeapTupleIsValid ( tp ) ) elog ( ERROR , "operator %u is not a member of opfamily %u" , opno , opfamily ) ;
 amop_tup = ( Form_pg_amop ) GETSTRUCT ( tp ) ;
 * strategy = amop_tup -> amopstrategy ;
 * lefttype = amop_tup -> amoplefttype ;
 * righttype = amop_tup -> amoprighttype ;
 ReleaseSysCache ( tp ) ;
 }