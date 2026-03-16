static Datum ExecEvalScalarVarFast ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Var * variable = ( Var * ) exprstate -> expr ;
 TupleTableSlot * slot ;
 AttrNumber attnum ;
 if ( isDone ) * isDone = ExprSingleResult ;
 switch ( variable -> varno ) {
 case INNER_VAR : slot = econtext -> ecxt_innertuple ;
 break ;
 case OUTER_VAR : slot = econtext -> ecxt_outertuple ;
 break ;
 default : slot = econtext -> ecxt_scantuple ;
 break ;
 }
 attnum = variable -> varattno ;
 return slot_getattr ( slot , attnum , isNull ) ;
 }