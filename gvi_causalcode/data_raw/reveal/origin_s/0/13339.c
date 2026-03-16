List * get_mergejoin_opfamilies ( Oid opno ) {
 List * result = NIL ;
 CatCList * catlist ;
 int i ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop aform = ( Form_pg_amop ) GETSTRUCT ( tuple ) ;
 if ( aform -> amopmethod == BTREE_AM_OID && aform -> amopstrategy == BTEqualStrategyNumber ) result = lappend_oid ( result , aform -> amopfamily ) ;
 }
 ReleaseSysCacheList ( catlist ) ;
 return result ;
 }