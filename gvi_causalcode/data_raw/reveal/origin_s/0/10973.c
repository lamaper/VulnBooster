static Datum ExecEvalCurrentOfExpr ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "WHERE CURRENT OF is not supported for this table type" ) ) ) ;
 return 0 ;
 }