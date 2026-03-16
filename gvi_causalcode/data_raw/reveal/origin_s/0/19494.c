static Datum ExecEvalDistinct ( FuncExprState * fcache , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Datum result ;
 FunctionCallInfo fcinfo ;
 ExprDoneCond argDone ;
 * isNull = false ;
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( fcache -> func . fn_oid == InvalidOid ) {
 DistinctExpr * op = ( DistinctExpr * ) fcache -> xprstate . expr ;
 init_fcache ( op -> opfuncid , op -> inputcollid , fcache , econtext -> ecxt_per_query_memory , true ) ;
 Assert ( ! fcache -> func . fn_retset ) ;
 }
 fcinfo = & fcache -> fcinfo_data ;
 argDone = ExecEvalFuncArgs ( fcinfo , fcache -> args , econtext ) ;
 if ( argDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "IS DISTINCT FROM does not support set arguments" ) ) ) ;
 Assert ( fcinfo -> nargs == 2 ) ;
 if ( fcinfo -> argnull [ 0 ] && fcinfo -> argnull [ 1 ] ) {
 result = BoolGetDatum ( FALSE ) ;
 }
 else if ( fcinfo -> argnull [ 0 ] || fcinfo -> argnull [ 1 ] ) {
 result = BoolGetDatum ( TRUE ) ;
 }
 else {
 fcinfo -> isnull = false ;
 result = FunctionCallInvoke ( fcinfo ) ;
 * isNull = fcinfo -> isnull ;
 result = BoolGetDatum ( ! DatumGetBool ( result ) ) ;
 }
 return result ;
 }