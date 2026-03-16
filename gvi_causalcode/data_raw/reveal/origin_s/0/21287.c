static Datum ExecEvalNullIf ( FuncExprState * nullIfExpr , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Datum result ;
 FunctionCallInfo fcinfo ;
 ExprDoneCond argDone ;
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( nullIfExpr -> func . fn_oid == InvalidOid ) {
 NullIfExpr * op = ( NullIfExpr * ) nullIfExpr -> xprstate . expr ;
 init_fcache ( op -> opfuncid , op -> inputcollid , nullIfExpr , econtext -> ecxt_per_query_memory , true ) ;
 Assert ( ! nullIfExpr -> func . fn_retset ) ;
 }
 fcinfo = & nullIfExpr -> fcinfo_data ;
 argDone = ExecEvalFuncArgs ( fcinfo , nullIfExpr -> args , econtext ) ;
 if ( argDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "NULLIF does not support set arguments" ) ) ) ;
 Assert ( fcinfo -> nargs == 2 ) ;
 if ( ! fcinfo -> argnull [ 0 ] && ! fcinfo -> argnull [ 1 ] ) {
 fcinfo -> isnull = false ;
 result = FunctionCallInvoke ( fcinfo ) ;
 if ( ! fcinfo -> isnull && DatumGetBool ( result ) ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 }
 * isNull = fcinfo -> argnull [ 0 ] ;
 return fcinfo -> arg [ 0 ] ;
 }