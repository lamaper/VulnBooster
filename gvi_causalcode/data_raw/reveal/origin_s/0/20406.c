List * get_op_btree_interpretation ( Oid opno ) {
 List * result = NIL ;
 OpBtreeInterpretation * thisresult ;
 CatCList * catlist ;
 int i ;
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( opno ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple op_tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop op_form = ( Form_pg_amop ) GETSTRUCT ( op_tuple ) ;
 StrategyNumber op_strategy ;
 if ( op_form -> amopmethod != BTREE_AM_OID ) continue ;
 op_strategy = ( StrategyNumber ) op_form -> amopstrategy ;
 Assert ( op_strategy >= 1 && op_strategy <= 5 ) ;
 thisresult = ( OpBtreeInterpretation * ) palloc ( sizeof ( OpBtreeInterpretation ) ) ;
 thisresult -> opfamily_id = op_form -> amopfamily ;
 thisresult -> strategy = op_strategy ;
 thisresult -> oplefttype = op_form -> amoplefttype ;
 thisresult -> oprighttype = op_form -> amoprighttype ;
 result = lappend ( result , thisresult ) ;
 }
 ReleaseSysCacheList ( catlist ) ;
 if ( result == NIL ) {
 Oid op_negator = get_negator ( opno ) ;
 if ( OidIsValid ( op_negator ) ) {
 catlist = SearchSysCacheList1 ( AMOPOPID , ObjectIdGetDatum ( op_negator ) ) ;
 for ( i = 0 ;
 i < catlist -> n_members ;
 i ++ ) {
 HeapTuple op_tuple = & catlist -> members [ i ] -> tuple ;
 Form_pg_amop op_form = ( Form_pg_amop ) GETSTRUCT ( op_tuple ) ;
 StrategyNumber op_strategy ;
 if ( op_form -> amopmethod != BTREE_AM_OID ) continue ;
 op_strategy = ( StrategyNumber ) op_form -> amopstrategy ;
 Assert ( op_strategy >= 1 && op_strategy <= 5 ) ;
 if ( op_strategy != BTEqualStrategyNumber ) continue ;
 thisresult = ( OpBtreeInterpretation * ) palloc ( sizeof ( OpBtreeInterpretation ) ) ;
 thisresult -> opfamily_id = op_form -> amopfamily ;
 thisresult -> strategy = ROWCOMPARE_NE ;
 thisresult -> oplefttype = op_form -> amoplefttype ;
 thisresult -> oprighttype = op_form -> amoprighttype ;
 result = lappend ( result , thisresult ) ;
 }
 ReleaseSysCacheList ( catlist ) ;
 }
 }
 return result ;
 }