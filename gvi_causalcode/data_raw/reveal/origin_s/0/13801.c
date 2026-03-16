Selectivity nulltestsel ( PlannerInfo * root , NullTestType nulltesttype , Node * arg , int varRelid , JoinType jointype , SpecialJoinInfo * sjinfo ) {
 VariableStatData vardata ;
 double selec ;
 examine_variable ( root , arg , varRelid , & vardata ) ;
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) {
 Form_pg_statistic stats ;
 double freq_null ;
 stats = ( Form_pg_statistic ) GETSTRUCT ( vardata . statsTuple ) ;
 freq_null = stats -> stanullfrac ;
 switch ( nulltesttype ) {
 case IS_NULL : selec = freq_null ;
 break ;
 case IS_NOT_NULL : selec = 1.0 - freq_null ;
 break ;
 default : elog ( ERROR , "unrecognized nulltesttype: %d" , ( int ) nulltesttype ) ;
 return ( Selectivity ) 0 ;
 }
 }
 else {
 switch ( nulltesttype ) {
 case IS_NULL : selec = DEFAULT_UNK_SEL ;
 break ;
 case IS_NOT_NULL : selec = DEFAULT_NOT_UNK_SEL ;
 break ;
 default : elog ( ERROR , "unrecognized nulltesttype: %d" , ( int ) nulltesttype ) ;
 return ( Selectivity ) 0 ;
 }
 }
 ReleaseVariableStats ( vardata ) ;
 CLAMP_PROBABILITY ( selec ) ;
 return ( Selectivity ) selec ;
 }