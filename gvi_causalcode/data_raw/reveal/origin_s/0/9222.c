static Datum ExecEvalAnd ( BoolExprState * andExpr , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 List * clauses = andExpr -> args ;
 ListCell * clause ;
 bool AnyNull ;
 if ( isDone ) * isDone = ExprSingleResult ;
 AnyNull = false ;
 foreach ( clause , clauses ) {
 ExprState * clausestate = ( ExprState * ) lfirst ( clause ) ;
 Datum clause_value ;
 clause_value = ExecEvalExpr ( clausestate , econtext , isNull , NULL ) ;
 if ( * isNull ) AnyNull = true ;
 else if ( ! DatumGetBool ( clause_value ) ) return clause_value ;
 }
 * isNull = AnyNull ;
 return BoolGetDatum ( ! AnyNull ) ;
 }