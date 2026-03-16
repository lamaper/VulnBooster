static Datum ExecEvalCase ( CaseExprState * caseExpr , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 List * clauses = caseExpr -> args ;
 ListCell * clause ;
 Datum save_datum ;
 bool save_isNull ;
 if ( isDone ) * isDone = ExprSingleResult ;
 save_datum = econtext -> caseValue_datum ;
 save_isNull = econtext -> caseValue_isNull ;
 if ( caseExpr -> arg ) {
 econtext -> caseValue_datum = ExecEvalExpr ( caseExpr -> arg , econtext , & econtext -> caseValue_isNull , NULL ) ;
 }
 foreach ( clause , clauses ) {
 CaseWhenState * wclause = lfirst ( clause ) ;
 Datum clause_value ;
 clause_value = ExecEvalExpr ( wclause -> expr , econtext , isNull , NULL ) ;
 if ( DatumGetBool ( clause_value ) && ! * isNull ) {
 econtext -> caseValue_datum = save_datum ;
 econtext -> caseValue_isNull = save_isNull ;
 return ExecEvalExpr ( wclause -> result , econtext , isNull , isDone ) ;
 }
 }
 econtext -> caseValue_datum = save_datum ;
 econtext -> caseValue_isNull = save_isNull ;
 if ( caseExpr -> defresult ) {
 return ExecEvalExpr ( caseExpr -> defresult , econtext , isNull , isDone ) ;
 }
 * isNull = true ;
 return ( Datum ) 0 ;
 }