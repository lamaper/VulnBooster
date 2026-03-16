Tuplestorestate * ExecMakeTableFunctionResult ( ExprState * funcexpr , ExprContext * econtext , MemoryContext argContext , TupleDesc expectedDesc , bool randomAccess ) {
 Tuplestorestate * tupstore = NULL ;
 TupleDesc tupdesc = NULL ;
 Oid funcrettype ;
 bool returnsTuple ;
 bool returnsSet = false ;
 FunctionCallInfoData fcinfo ;
 PgStat_FunctionCallUsage fcusage ;
 ReturnSetInfo rsinfo ;
 HeapTupleData tmptup ;
 MemoryContext callerContext ;
 MemoryContext oldcontext ;
 bool direct_function_call ;
 bool first_time = true ;
 callerContext = CurrentMemoryContext ;
 funcrettype = exprType ( ( Node * ) funcexpr -> expr ) ;
 returnsTuple = type_is_rowtype ( funcrettype ) ;
 rsinfo . type = T_ReturnSetInfo ;
 rsinfo . econtext = econtext ;
 rsinfo . expectedDesc = expectedDesc ;
 rsinfo . allowedModes = ( int ) ( SFRM_ValuePerCall | SFRM_Materialize | SFRM_Materialize_Preferred ) ;
 if ( randomAccess ) rsinfo . allowedModes |= ( int ) SFRM_Materialize_Random ;
 rsinfo . returnMode = SFRM_ValuePerCall ;
 rsinfo . setResult = NULL ;
 rsinfo . setDesc = NULL ;
 if ( funcexpr && IsA ( funcexpr , FuncExprState ) && IsA ( funcexpr -> expr , FuncExpr ) ) {
 FuncExprState * fcache = ( FuncExprState * ) funcexpr ;
 ExprDoneCond argDone ;
 direct_function_call = true ;
 if ( fcache -> func . fn_oid == InvalidOid ) {
 FuncExpr * func = ( FuncExpr * ) fcache -> xprstate . expr ;
 init_fcache ( func -> funcid , func -> inputcollid , fcache , econtext -> ecxt_per_query_memory , false ) ;
 }
 returnsSet = fcache -> func . fn_retset ;
 InitFunctionCallInfoData ( fcinfo , & ( fcache -> func ) , list_length ( fcache -> args ) , fcache -> fcinfo_data . fncollation , NULL , ( Node * ) & rsinfo ) ;
 MemoryContextReset ( argContext ) ;
 oldcontext = MemoryContextSwitchTo ( argContext ) ;
 argDone = ExecEvalFuncArgs ( & fcinfo , fcache -> args , econtext ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 if ( argDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "set-valued function called in context that cannot accept a set" ) ) ) ;
 if ( fcache -> func . fn_strict ) {
 int i ;
 for ( i = 0 ;
 i < fcinfo . nargs ;
 i ++ ) {
 if ( fcinfo . argnull [ i ] ) goto no_function_result ;
 }
 }
 }
 else {
 direct_function_call = false ;
 InitFunctionCallInfoData ( fcinfo , NULL , 0 , InvalidOid , NULL , NULL ) ;
 }
 MemoryContextSwitchTo ( econtext -> ecxt_per_tuple_memory ) ;
 for ( ;
 ;
 ) {
 Datum result ;
 CHECK_FOR_INTERRUPTS ( ) ;
 ResetExprContext ( econtext ) ;
 if ( direct_function_call ) {
 pgstat_init_function_usage ( & fcinfo , & fcusage ) ;
 fcinfo . isnull = false ;
 rsinfo . isDone = ExprSingleResult ;
 result = FunctionCallInvoke ( & fcinfo ) ;
 pgstat_end_function_usage ( & fcusage , rsinfo . isDone != ExprMultipleResult ) ;
 }
 else {
 result = ExecEvalExpr ( funcexpr , econtext , & fcinfo . isnull , & rsinfo . isDone ) ;
 }
 if ( rsinfo . returnMode == SFRM_ValuePerCall ) {
 if ( rsinfo . isDone == ExprEndResult ) break ;
 if ( first_time ) {
 oldcontext = MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 tupstore = tuplestore_begin_heap ( randomAccess , false , work_mem ) ;
 rsinfo . setResult = tupstore ;
 if ( ! returnsTuple ) {
 tupdesc = CreateTemplateTupleDesc ( 1 , false ) ;
 TupleDescInitEntry ( tupdesc , ( AttrNumber ) 1 , "column" , funcrettype , - 1 , 0 ) ;
 rsinfo . setDesc = tupdesc ;
 }
 MemoryContextSwitchTo ( oldcontext ) ;
 }
 if ( returnsTuple ) {
 if ( ! fcinfo . isnull ) {
 HeapTupleHeader td = DatumGetHeapTupleHeader ( result ) ;
 if ( tupdesc == NULL ) {
 oldcontext = MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 tupdesc = lookup_rowtype_tupdesc_copy ( HeapTupleHeaderGetTypeId ( td ) , HeapTupleHeaderGetTypMod ( td ) ) ;
 rsinfo . setDesc = tupdesc ;
 MemoryContextSwitchTo ( oldcontext ) ;
 }
 else {
 if ( HeapTupleHeaderGetTypeId ( td ) != tupdesc -> tdtypeid || HeapTupleHeaderGetTypMod ( td ) != tupdesc -> tdtypmod ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "rows returned by function are not all of the same row type" ) ) ) ;
 }
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( td ) ;
 tmptup . t_data = td ;
 tuplestore_puttuple ( tupstore , & tmptup ) ;
 }
 else {
 int natts = expectedDesc -> natts ;
 bool * nullflags ;
 nullflags = ( bool * ) palloc ( natts * sizeof ( bool ) ) ;
 memset ( nullflags , true , natts * sizeof ( bool ) ) ;
 tuplestore_putvalues ( tupstore , expectedDesc , NULL , nullflags ) ;
 }
 }
 else {
 tuplestore_putvalues ( tupstore , tupdesc , & result , & fcinfo . isnull ) ;
 }
 if ( rsinfo . isDone != ExprMultipleResult ) break ;
 }
 else if ( rsinfo . returnMode == SFRM_Materialize ) {
 if ( ! first_time || rsinfo . isDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_E_R_I_E_SRF_PROTOCOL_VIOLATED ) , errmsg ( "table-function protocol for materialize mode was not followed" ) ) ) ;
 break ;
 }
 else ereport ( ERROR , ( errcode ( ERRCODE_E_R_I_E_SRF_PROTOCOL_VIOLATED ) , errmsg ( "unrecognized table-function returnMode: %d" , ( int ) rsinfo . returnMode ) ) ) ;
 first_time = false ;
 }
 no_function_result : if ( rsinfo . setResult == NULL ) {
 MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 tupstore = tuplestore_begin_heap ( randomAccess , false , work_mem ) ;
 rsinfo . setResult = tupstore ;
 if ( ! returnsSet ) {
 int natts = expectedDesc -> natts ;
 bool * nullflags ;
 MemoryContextSwitchTo ( econtext -> ecxt_per_tuple_memory ) ;
 nullflags = ( bool * ) palloc ( natts * sizeof ( bool ) ) ;
 memset ( nullflags , true , natts * sizeof ( bool ) ) ;
 tuplestore_putvalues ( tupstore , expectedDesc , NULL , nullflags ) ;
 }
 }
 if ( rsinfo . setDesc ) {
 tupledesc_match ( expectedDesc , rsinfo . setDesc ) ;
 if ( rsinfo . setDesc -> tdrefcount == - 1 ) FreeTupleDesc ( rsinfo . setDesc ) ;
 }
 MemoryContextSwitchTo ( callerContext ) ;
 return rsinfo . setResult ;
 }