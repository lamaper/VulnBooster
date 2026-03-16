static Datum ExecMakeFunctionResult ( FuncExprState * fcache , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 List * arguments ;
 Datum result ;
 FunctionCallInfo fcinfo ;
 PgStat_FunctionCallUsage fcusage ;
 ReturnSetInfo rsinfo ;
 ExprDoneCond argDone ;
 bool hasSetArg ;
 int i ;
 restart : check_stack_depth ( ) ;
 if ( fcache -> funcResultStore ) {
 Assert ( isDone ) ;
 if ( tuplestore_gettupleslot ( fcache -> funcResultStore , true , false , fcache -> funcResultSlot ) ) {
 * isDone = ExprMultipleResult ;
 if ( fcache -> funcReturnsTuple ) {
 * isNull = false ;
 return ExecFetchSlotTupleDatum ( fcache -> funcResultSlot ) ;
 }
 else {
 return slot_getattr ( fcache -> funcResultSlot , 1 , isNull ) ;
 }
 }
 tuplestore_end ( fcache -> funcResultStore ) ;
 fcache -> funcResultStore = NULL ;
 if ( ! fcache -> setHasSetArg ) {
 * isDone = ExprEndResult ;
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 Assert ( ! fcache -> setArgsValid ) ;
 }
 fcinfo = & fcache -> fcinfo_data ;
 arguments = fcache -> args ;
 if ( ! fcache -> setArgsValid ) {
 argDone = ExecEvalFuncArgs ( fcinfo , arguments , econtext ) ;
 if ( argDone == ExprEndResult ) {
 * isNull = true ;
 if ( isDone ) * isDone = ExprEndResult ;
 else ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "set-valued function called in context that cannot accept a set" ) ) ) ;
 return ( Datum ) 0 ;
 }
 hasSetArg = ( argDone != ExprSingleResult ) ;
 }
 else {
 hasSetArg = fcache -> setHasSetArg ;
 fcache -> setArgsValid = false ;
 }
 if ( fcache -> func . fn_retset || hasSetArg ) {
 if ( isDone == NULL ) ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "set-valued function called in context that cannot accept a set" ) ) ) ;
 if ( fcache -> func . fn_retset ) fcinfo -> resultinfo = ( Node * ) & rsinfo ;
 rsinfo . type = T_ReturnSetInfo ;
 rsinfo . econtext = econtext ;
 rsinfo . expectedDesc = fcache -> funcResultDesc ;
 rsinfo . allowedModes = ( int ) ( SFRM_ValuePerCall | SFRM_Materialize ) ;
 rsinfo . returnMode = SFRM_ValuePerCall ;
 rsinfo . setResult = NULL ;
 rsinfo . setDesc = NULL ;
 for ( ;
 ;
 ) {
 bool callit = true ;
 if ( fcache -> func . fn_strict ) {
 for ( i = 0 ;
 i < fcinfo -> nargs ;
 i ++ ) {
 if ( fcinfo -> argnull [ i ] ) {
 callit = false ;
 break ;
 }
 }
 }
 if ( callit ) {
 pgstat_init_function_usage ( fcinfo , & fcusage ) ;
 fcinfo -> isnull = false ;
 rsinfo . isDone = ExprSingleResult ;
 result = FunctionCallInvoke ( fcinfo ) ;
 * isNull = fcinfo -> isnull ;
 * isDone = rsinfo . isDone ;
 pgstat_end_function_usage ( & fcusage , rsinfo . isDone != ExprMultipleResult ) ;
 }
 else if ( fcache -> func . fn_retset ) {
 result = ( Datum ) 0 ;
 * isNull = true ;
 * isDone = ExprEndResult ;
 }
 else {
 result = ( Datum ) 0 ;
 * isNull = true ;
 * isDone = ExprSingleResult ;
 }
 if ( rsinfo . returnMode == SFRM_ValuePerCall ) {
 if ( * isDone != ExprEndResult ) {
 if ( fcache -> func . fn_retset && * isDone == ExprMultipleResult ) {
 fcache -> setHasSetArg = hasSetArg ;
 fcache -> setArgsValid = true ;
 if ( ! fcache -> shutdown_reg ) {
 RegisterExprContextCallback ( econtext , ShutdownFuncExpr , PointerGetDatum ( fcache ) ) ;
 fcache -> shutdown_reg = true ;
 }
 }
 if ( hasSetArg ) * isDone = ExprMultipleResult ;
 break ;
 }
 }
 else if ( rsinfo . returnMode == SFRM_Materialize ) {
 if ( rsinfo . isDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_E_R_I_E_SRF_PROTOCOL_VIOLATED ) , errmsg ( "table-function protocol for materialize mode was not followed" ) ) ) ;
 if ( rsinfo . setResult != NULL ) {
 ExecPrepareTuplestoreResult ( fcache , econtext , rsinfo . setResult , rsinfo . setDesc ) ;
 fcache -> setHasSetArg = hasSetArg ;
 goto restart ;
 }
 * isDone = ExprEndResult ;
 * isNull = true ;
 result = ( Datum ) 0 ;
 }
 else ereport ( ERROR , ( errcode ( ERRCODE_E_R_I_E_SRF_PROTOCOL_VIOLATED ) , errmsg ( "unrecognized table-function returnMode: %d" , ( int ) rsinfo . returnMode ) ) ) ;
 if ( ! hasSetArg ) break ;
 argDone = ExecEvalFuncArgs ( fcinfo , arguments , econtext ) ;
 if ( argDone != ExprMultipleResult ) {
 * isNull = true ;
 * isDone = ExprEndResult ;
 result = ( Datum ) 0 ;
 break ;
 }
 }
 }
 else {
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( fcache -> func . fn_strict ) {
 for ( i = 0 ;
 i < fcinfo -> nargs ;
 i ++ ) {
 if ( fcinfo -> argnull [ i ] ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 }
 }
 pgstat_init_function_usage ( fcinfo , & fcusage ) ;
 fcinfo -> isnull = false ;
 result = FunctionCallInvoke ( fcinfo ) ;
 * isNull = fcinfo -> isnull ;
 pgstat_end_function_usage ( & fcusage , true ) ;
 }
 return result ;
 }