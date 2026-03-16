bool get_compatible_hash_operators ( Oid opno , Oid * lhs_opno , Oid * rhs_opno ) {
 bool result = false ;
 CatCList * catlist ;
 int i ;
 if ( lhs_opno ) * lhs_opno = InvalidOid ;
 if ( rhs_opno ) * rhs_opno = InvalidOid ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop aform = ( Form_pg_amop ) GETSTRUCT ( tuple ) ;
 if ( aform -> amopmethod == HASH_AM_OID && aform -> amopstrategy == HTEqualStrategyNumber ) {
 if ( aform -> amoplefttype == aform -> amoprighttype ) {
 if ( lhs_opno ) * lhs_opno = opno ;
 if ( rhs_opno ) * rhs_opno = opno ;
 result = true ;
 break ;
 }
 if ( lhs_opno ) {
 * lhs_opno = get_opfamily_member ( aform -> amopfamily , aform -> amoplefttype , aform -> amoplefttype , HTEqualStrategyNumber ) ;
 if ( ! OidIsValid ( * lhs_opno ) ) continue ;
 if ( ! rhs_opno ) {
 result = true ;
 break ;
 }
 }
 if ( rhs_opno ) {
 * rhs_opno = get_opfamily_member ( aform -> amopfamily , aform -> amoprighttype , aform -> amoprighttype , HTEqualStrategyNumber ) ;
 if ( ! OidIsValid ( * rhs_opno ) ) {
 if ( lhs_opno ) * lhs_opno = InvalidOid ;
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