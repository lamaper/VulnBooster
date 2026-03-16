static Datum ExecEvalWholeRowVar ( WholeRowVarExprState * wrvstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Var * variable = ( Var * ) wrvstate -> xprstate . expr ;
 TupleTableSlot * slot ;
 TupleDesc output_tupdesc ;
 MemoryContext oldcontext ;
 bool needslow = false ;
 if ( isDone ) * isDone = ExprSingleResult ;
 Assert ( variable -> varattno == InvalidAttrNumber ) ;
 switch ( variable -> varno ) {
 case INNER_VAR : slot = econtext -> ecxt_innertuple ;
 break ;
 case OUTER_VAR : slot = econtext -> ecxt_outertuple ;
 break ;
 default : slot = econtext -> ecxt_scantuple ;
 break ;
 }
 if ( wrvstate -> parent ) {
 PlanState * subplan = NULL ;
 switch ( nodeTag ( wrvstate -> parent ) ) {
 case T_SubqueryScanState : subplan = ( ( SubqueryScanState * ) wrvstate -> parent ) -> subplan ;
 break ;
 case T_CteScanState : subplan = ( ( CteScanState * ) wrvstate -> parent ) -> cteplanstate ;
 break ;
 default : break ;
 }
 if ( subplan ) {
 bool junk_filter_needed = false ;
 ListCell * tlist ;
 foreach ( tlist , subplan -> plan -> targetlist ) {
 TargetEntry * tle = ( TargetEntry * ) lfirst ( tlist ) ;
 if ( tle -> resjunk ) {
 junk_filter_needed = true ;
 break ;
 }
 }
 if ( junk_filter_needed ) {
 oldcontext = MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 wrvstate -> wrv_junkFilter = ExecInitJunkFilter ( subplan -> plan -> targetlist , ExecGetResultType ( subplan ) -> tdhasoid , ExecInitExtraTupleSlot ( wrvstate -> parent -> state ) ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 }
 }
 }
 if ( wrvstate -> wrv_junkFilter != NULL ) slot = ExecFilterJunk ( wrvstate -> wrv_junkFilter , slot ) ;
 if ( variable -> vartype != RECORDOID ) {
 TupleDesc var_tupdesc ;
 TupleDesc slot_tupdesc ;
 int i ;
 var_tupdesc = lookup_rowtype_tupdesc ( variable -> vartype , - 1 ) ;
 slot_tupdesc = slot -> tts_tupleDescriptor ;
 if ( var_tupdesc -> natts != slot_tupdesc -> natts ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "table row type and query-specified row type do not match" ) , errdetail_plural ( "Table row contains %d attribute, but query expects %d." , "Table row contains %d attributes, but query expects %d." , slot_tupdesc -> natts , slot_tupdesc -> natts , var_tupdesc -> natts ) ) ) ;
 for ( i = 0 ;
 i < var_tupdesc -> natts ;
 i ++ ) {
 Form_pg_attribute vattr = var_tupdesc -> attrs [ i ] ;
 Form_pg_attribute sattr = slot_tupdesc -> attrs [ i ] ;
 if ( vattr -> atttypid == sattr -> atttypid ) continue ;
 if ( ! vattr -> attisdropped ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "table row type and query-specified row type do not match" ) , errdetail ( "Table has type %s at ordinal position %d, but query expects %s." , format_type_be ( sattr -> atttypid ) , i + 1 , format_type_be ( vattr -> atttypid ) ) ) ) ;
 if ( vattr -> attlen != sattr -> attlen || vattr -> attalign != sattr -> attalign ) needslow = true ;
 }
 oldcontext = MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 output_tupdesc = CreateTupleDescCopy ( var_tupdesc ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 ReleaseTupleDesc ( var_tupdesc ) ;
 }
 else {
 oldcontext = MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 output_tupdesc = CreateTupleDescCopy ( slot -> tts_tupleDescriptor ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 }
 if ( econtext -> ecxt_estate && variable -> varno <= list_length ( econtext -> ecxt_estate -> es_range_table ) ) {
 RangeTblEntry * rte = rt_fetch ( variable -> varno , econtext -> ecxt_estate -> es_range_table ) ;
 if ( rte -> eref ) ExecTypeSetColNames ( output_tupdesc , rte -> eref -> colnames ) ;
 }
 wrvstate -> wrv_tupdesc = BlessTupleDesc ( output_tupdesc ) ;
 if ( needslow ) wrvstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalWholeRowSlow ;
 else wrvstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalWholeRowFast ;
 return ( * wrvstate -> xprstate . evalfunc ) ( ( ExprState * ) wrvstate , econtext , isNull , isDone ) ;
 }