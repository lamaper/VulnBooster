bool op_in_opfamily ( Oid opno , Oid opfamily ) {
 return SearchSysCacheExists3 ( AMOPOPID , ObjectIdGetDatum ( opno ) , CharGetDatum ( AMOP_SEARCH ) , ObjectIdGetDatum ( opfamily ) ) ;
 }