bool equality_ops_are_compatible ( Oid opno1 , Oid opno2 ) {
 bool result ;
 CatCList * catlist ;
 int i ;
 if ( opno1 == opno2 ) return true ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno1 ) ) ;
 result = false ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple op_tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop op_form = ( Form_pg_amop ) GETSTRUCT ( op_tuple ) ;
 if ( op_form -> amopmethod == BTREE_AM_OID || op_form -> amopmethod == HASH_AM_OID ) {
 if ( op_in_opfamily ( opno2 , op_form -> amopfamily ) ) {
 result = true ;
 break ;
 }
 }
 }
 ReleaseSysCacheList ( catlist ) ;
 return result ;
 }