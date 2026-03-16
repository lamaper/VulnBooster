static Datum ExecEvalWholeRowSlow ( WholeRowVarExprState * wrvstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Var * variable = ( Var * ) wrvstate -> xprstate . expr ;
 TupleTableSlot * slot ;
 HeapTuple tuple ;
 TupleDesc tupleDesc ;
 TupleDesc var_tupdesc ;
 HeapTupleHeader dtuple ;
 int i ;
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
 tuple = ExecFetchSlotTuple ( slot ) ;
 tupleDesc = slot -> tts_tupleDescriptor ;
 Assert ( variable -> vartype != RECORDOID ) ;
 var_tupdesc = wrvstate -> wrv_tupdesc ;
 for ( i = 0 ;
 i < var_tupdesc -> natts ;
 i ++ ) {
 Form_pg_attribute vattr = var_tupdesc -> attrs [ i ] ;
 Form_pg_attribute sattr = tupleDesc -> attrs [ i ] ;
 if ( ! vattr -> attisdropped ) continue ;
 if ( heap_attisnull ( tuple , i + 1 ) ) continue ;
 if ( vattr -> attlen != sattr -> attlen || vattr -> attalign != sattr -> attalign ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "table row type and query-specified row type do not match" ) , errdetail ( "Physical storage mismatch on dropped attribute at ordinal position %d." , i + 1 ) ) ) ;
 }
 dtuple = DatumGetHeapTupleHeader ( ExecFetchSlotTupleDatum ( slot ) ) ;
 HeapTupleHeaderSetTypeId ( dtuple , wrvstate -> wrv_tupdesc -> tdtypeid ) ;
 HeapTupleHeaderSetTypMod ( dtuple , wrvstate -> wrv_tupdesc -> tdtypmod ) ;
 return PointerGetDatum ( dtuple ) ;
 }