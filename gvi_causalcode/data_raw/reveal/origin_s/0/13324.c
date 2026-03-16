static Datum ExecEvalWindowFunc ( WindowFuncExprState * wfunc , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( econtext -> ecxt_aggvalues == NULL ) elog ( ERROR , "no window functions in this expression context" ) ;
 * isNull = econtext -> ecxt_aggnulls [ wfunc -> wfuncno ] ;
 return econtext -> ecxt_aggvalues [ wfunc -> wfuncno ] ;
 }