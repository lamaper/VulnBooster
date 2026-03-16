static Datum ExecEvalCaseTestExpr ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = econtext -> caseValue_isNull ;
 return econtext -> caseValue_datum ;
 }