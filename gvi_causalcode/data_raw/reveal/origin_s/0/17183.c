Selectivity booltestsel ( PlannerInfo * root , BoolTestType booltesttype , Node * arg , int varRelid , JoinType jointype , SpecialJoinInfo * sjinfo ) {
 VariableStatData vardata ;
 double selec ;
 examine_variable ( root , arg , varRelid , & vardata ) ;
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) {
 Form_pg_statistic stats ;
 double freq_null ;
 Datum * values ;
 int nvalues ;
 float4 * numbers ;
 int nnumbers ;
 stats = ( Form_pg_statistic ) GETSTRUCT ( vardata . statsTuple ) ;
 freq_null = stats -> stanullfrac ;
 if ( get_attstatsslot ( vardata . statsTuple , vardata . atttype , vardata . atttypmod , STATISTIC_KIND_MCV , InvalidOid , NULL , & values , & nvalues , & numbers , & nnumbers ) && nnumbers > 0 ) {
 double freq_true ;
 double freq_false ;
 if ( DatumGetBool ( values [ 0 ] ) ) freq_true = numbers [ 0 ] ;
 else freq_true = 1.0 - numbers [ 0 ] - freq_null ;
 freq_false = 1.0 - freq_true - freq_null ;
 switch ( booltesttype ) {
 case IS_UNKNOWN : selec = freq_null ;
 break ;
 case IS_NOT_UNKNOWN : selec = 1.0 - freq_null ;
 break ;
 case IS_TRUE : selec = freq_true ;
 break ;
 case IS_NOT_TRUE : selec = 1.0 - freq_true ;
 break ;
 case IS_FALSE : selec = freq_false ;
 break ;
 case IS_NOT_FALSE : selec = 1.0 - freq_false ;
 break ;
 default : elog ( ERROR , "unrecognized booltesttype: %d" , ( int ) booltesttype ) ;
 selec = 0.0 ;
 break ;
 }
 free_attstatsslot ( vardata . atttype , values , nvalues , numbers , nnumbers ) ;
 }
 else {
 switch ( booltesttype ) {
 case IS_UNKNOWN : selec = freq_null ;
 break ;
 case IS_NOT_UNKNOWN : selec = 1.0 - freq_null ;
 break ;
 case IS_TRUE : case IS_FALSE : selec = ( 1.0 - freq_null ) / 2.0 ;
 break ;
 case IS_NOT_TRUE : case IS_NOT_FALSE : selec = ( freq_null + 1.0 ) / 2.0 ;
 break ;
 default : elog ( ERROR , "unrecognized booltesttype: %d" , ( int ) booltesttype ) ;
 selec = 0.0 ;
 break ;
 }
 }
 }
 else {
 switch ( booltesttype ) {
 case IS_UNKNOWN : selec = DEFAULT_UNK_SEL ;
 break ;
 case IS_NOT_UNKNOWN : selec = DEFAULT_NOT_UNK_SEL ;
 break ;
 case IS_TRUE : case IS_NOT_FALSE : selec = ( double ) clause_selectivity ( root , arg , varRelid , jointype , sjinfo ) ;
 break ;
 case IS_FALSE : case IS_NOT_TRUE : selec = 1.0 - ( double ) clause_selectivity ( root , arg , varRelid , jointype , sjinfo ) ;
 break ;
 default : elog ( ERROR , "unrecognized booltesttype: %d" , ( int ) booltesttype ) ;
 selec = 0.0 ;
 break ;
 }
 }
 ReleaseVariableStats ( vardata ) ;
 CLAMP_PROBABILITY ( selec ) ;
 return ( Selectivity ) selec ;
 }