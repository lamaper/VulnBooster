static void ExecPrepareTuplestoreResult ( FuncExprState * fcache , ExprContext * econtext , Tuplestorestate * resultStore , TupleDesc resultDesc ) {
 fcache -> funcResultStore = resultStore ;
 if ( fcache -> funcResultSlot == NULL ) {
 TupleDesc slotDesc ;
 MemoryContext oldcontext ;
 oldcontext = MemoryContextSwitchTo ( fcache -> func . fn_mcxt ) ;
 if ( fcache -> funcResultDesc ) slotDesc = fcache -> funcResultDesc ;
 else if ( resultDesc ) {
 slotDesc = CreateTupleDescCopy ( resultDesc ) ;
 }
 else {
 ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "function returning setof record called in " "context that cannot accept type record" ) ) ) ;
 slotDesc = NULL ;
 }
 fcache -> funcResultSlot = MakeSingleTupleTableSlot ( slotDesc ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 }
 if ( resultDesc ) {
 if ( fcache -> funcResultDesc ) tupledesc_match ( fcache -> funcResultDesc , resultDesc ) ;
 if ( resultDesc -> tdrefcount == - 1 ) FreeTupleDesc ( resultDesc ) ;
 }
 if ( ! fcache -> shutdown_reg ) {
 RegisterExprContextCallback ( econtext , ShutdownFuncExpr , PointerGetDatum ( fcache ) ) ;
 fcache -> shutdown_reg = true ;
 }
 }