static Datum ExecEvalRelabelType ( GenericExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 return ExecEvalExpr ( exprstate -> arg , econtext , isNull , isDone ) ;
 }