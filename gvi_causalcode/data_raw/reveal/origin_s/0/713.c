Selectivity boolvarsel ( PlannerInfo * root , Node * arg , int varRelid ) {
 VariableStatData vardata ;
 double selec ;
 examine_variable ( root , arg , varRelid , & vardata ) ;
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) {
 selec = var_eq_const ( & vardata , BooleanEqualOperator , BoolGetDatum ( true ) , false , true ) ;
 }
 else if ( is_funcclause ( arg ) ) {
 selec = 0.3333333 ;
 }
 else {
 selec = 0.5 ;
 }
 ReleaseVariableStats ( vardata ) ;
 return selec ;
 }