bool get_op_hash_functions ( Oid opno , RegProcedure * lhs_procno , RegProcedure * rhs_procno ) {
 bool result = false ;
 CatCList * catlist ;
 int i ;
 if ( lhs_procno ) * lhs_procno = InvalidOid ;
 if ( rhs_procno ) * rhs_procno = InvalidOid ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop aform = ( Form_pg_amop ) GETSTRUCT ( tuple ) ;
 if ( aform -> amopmethod == HASH_AM_OID && aform -> amopstrategy == HTEqualStrategyNumber ) {
 if ( lhs_procno ) {
 * lhs_procno = get_opfamily_proc ( aform -> amopfamily , aform -> amoplefttype , aform -> amoplefttype , HASHPROC ) ;
 if ( ! OidIsValid ( * lhs_procno ) ) continue ;
 if ( ! rhs_procno ) {
 result = true ;
 break ;
 }
 if ( aform -> amoplefttype == aform -> amoprighttype ) {
 * rhs_procno = * lhs_procno ;
 result = true ;
 break ;
 }
 }
 if ( rhs_procno ) {
 * rhs_procno = get_opfamily_proc ( aform -> amopfamily , aform -> amoprighttype , aform -> amoprighttype , HASHPROC ) ;
 if ( ! OidIsValid ( * rhs_procno ) ) {
 if ( lhs_procno ) * lhs_procno = InvalidOid ;
 continue ;
 }
 result = true ;
 break ;
 }
 }
 }
 ReleaseSysCacheList ( catlist ) ;
 return result ;
 }