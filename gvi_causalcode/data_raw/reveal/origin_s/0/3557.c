static Datum ExecMakeFunctionResultNoSets ( FuncExprState * fcache , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ListCell * arg ;
 Datum result ;
 FunctionCallInfo fcinfo ;
 PgStat_FunctionCallUsage fcusage ;
 int i ;
 check_stack_depth ( ) ;
 if ( isDone ) * isDone = ExprSingleResult ;
 fcinfo = & fcache -> fcinfo_data ;
 i = 0 ;
 foreach ( arg , fcache -> args ) {
 ExprState * argstate = ( ExprState * ) lfirst ( arg ) ;
 fcinfo -> arg [ i ] = ExecEvalExpr ( argstate , econtext , & fcinfo -> argnull [ i ] , NULL ) ;
 i ++ ;
 }
 if ( fcache -> func . fn_strict ) {
 while ( -- i >= 0 ) {
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
 return result ;
 }