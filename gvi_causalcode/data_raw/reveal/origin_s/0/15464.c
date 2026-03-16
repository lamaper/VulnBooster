bool get_ordering_op_properties ( Oid opno , Oid * opfamily , Oid * opcintype , int16 * strategy ) {
 bool result = false ;
 CatCList * catlist ;
 int i ;
 * opfamily = InvalidOid ;
 * opcintype = InvalidOid ;
 * strategy = 0 ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop aform = ( Form_pg_amop ) GETSTRUCT ( tuple ) ;
 if ( aform -> amopmethod != BTREE_AM_OID ) continue ;
 if ( aform -> amopstrategy == BTLessStrategyNumber || aform -> amopstrategy == BTGreaterStrategyNumber ) {
 if ( aform -> amoplefttype == aform -> amoprighttype ) {
 * opfamily = aform -> amopfamily ;
 * opcintype = aform -> amoplefttype ;
 * strategy = aform -> amopstrategy ;
 result = true ;
 break ;
 }
 }
 }
 ReleaseSysCacheList ( catlist ) ;
 return result ;
 }