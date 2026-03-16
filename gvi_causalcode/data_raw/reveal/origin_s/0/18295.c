static Datum ExecEvalWholeRowFast ( WholeRowVarExprState * wrvstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Var * variable = ( Var * ) wrvstate -> xprstate . expr ;
 TupleTableSlot * slot ;
 HeapTupleHeader dtuple ;
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = false ;
 switch ( variable -> varno ) {
 case INNER_VAR : slot = econtext -> ecxt_innertuple ;
 break ;
 case OUTER_VAR : slot = econtext -> ecxt_outertuple ;
 break ;
 default : slot = econtext -> ecxt_scantuple ;
 break ;
 }
 if ( wrvstate -> wrv_junkFilter != NULL ) slot = ExecFilterJunk ( wrvstate -> wrv_junkFilter , slot ) ;
 dtuple = DatumGetHeapTupleHeader ( ExecFetchSlotTupleDatum ( slot ) ) ;
 HeapTupleHeaderSetTypeId ( dtuple , wrvstate -> wrv_tupdesc -> tdtypeid ) ;
 HeapTupleHeaderSetTypMod ( dtuple , wrvstate -> wrv_tupdesc -> tdtypmod ) ;
 return PointerGetDatum ( dtuple ) ;
 }