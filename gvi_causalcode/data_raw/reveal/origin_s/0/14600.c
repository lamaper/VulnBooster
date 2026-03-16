static Datum ExecEvalAggref ( AggrefExprState * aggref , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( econtext -> ecxt_aggvalues == NULL ) elog ( ERROR , "no aggregates in this expression context" ) ;
 * isNull = econtext -> ecxt_aggnulls [ aggref -> aggno ] ;
 return econtext -> ecxt_aggvalues [ aggref -> aggno ] ;
 }