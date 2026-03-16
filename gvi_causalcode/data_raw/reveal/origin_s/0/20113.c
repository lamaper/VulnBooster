static Datum ExecEvalNot ( BoolExprState * notclause , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ExprState * clause = linitial ( notclause -> args ) ;
 Datum expr_value ;
 if ( isDone ) * isDone = ExprSingleResult ;
 expr_value = ExecEvalExpr ( clause , econtext , isNull , NULL ) ;
 if ( * isNull ) return expr_value ;
 return BoolGetDatum ( ! DatumGetBool ( expr_value ) ) ;
 }