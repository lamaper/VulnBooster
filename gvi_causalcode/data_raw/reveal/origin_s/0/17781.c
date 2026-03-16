static Datum ExecEvalConst ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Const * con = ( Const * ) exprstate -> expr ;
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = con -> constisnull ;
 return con -> constvalue ;
 }