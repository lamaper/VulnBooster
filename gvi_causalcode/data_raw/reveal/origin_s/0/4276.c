static Datum ExecEvalCoerceToDomainValue ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = econtext -> domainValue_isNull ;
 return econtext -> domainValue_datum ;
 }