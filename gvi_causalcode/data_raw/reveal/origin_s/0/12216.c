static ExprDoneCond ExecEvalFuncArgs ( FunctionCallInfo fcinfo , List * argList , ExprContext * econtext ) {
 ExprDoneCond argIsDone ;
 int i ;
 ListCell * arg ;
 argIsDone = ExprSingleResult ;
 i = 0 ;
 foreach ( arg , argList ) {
 ExprState * argstate = ( ExprState * ) lfirst ( arg ) ;
 ExprDoneCond thisArgIsDone ;
 fcinfo -> arg [ i ] = ExecEvalExpr ( argstate , econtext , & fcinfo -> argnull [ i ] , & thisArgIsDone ) ;
 if ( thisArgIsDone != ExprSingleResult ) {
 if ( argIsDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "functions and operators can take at most one set argument" ) ) ) ;
 argIsDone = thisArgIsDone ;
 }
 i ++ ;
 }
 Assert ( i == fcinfo -> nargs ) ;
 return argIsDone ;
 }