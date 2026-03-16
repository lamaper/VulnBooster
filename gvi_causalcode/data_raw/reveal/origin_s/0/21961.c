Oid get_ordering_op_for_equality_op ( Oid opno , bool use_lhs_type ) {
 Oid result = InvalidOid ;
 CatCList * catlist ;
 int i ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop aform = ( Form_pg_amop ) GETSTRUCT ( tuple ) ;
 if ( aform -> amopmethod != BTREE_AM_OID ) continue ;
 if ( aform -> amopstrategy == BTEqualStrategyNumber ) {
 Oid typid ;
 typid = use_lhs_type ? aform -> amoplefttype : aform -> amoprighttype ;
 result = get_opfamily_member ( aform -> amopfamily , typid , typid , BTLessStrategyNumber ) ;
 if ( OidIsValid ( result ) ) break ;
 }
 }
 ReleaseSysCacheList ( catlist ) ;
 return result ;
 }