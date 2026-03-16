static Datum ExecEvalParamExec ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Param * expression = ( Param * ) exprstate -> expr ;
 int thisParamId = expression -> paramid ;
 ParamExecData * prm ;
 if ( isDone ) * isDone = ExprSingleResult ;
 prm = & ( econtext -> ecxt_param_exec_vals [ thisParamId ] ) ;
 if ( prm -> execPlan != NULL ) {
 ExecSetParamPlan ( prm -> execPlan , econtext ) ;
 Assert ( prm -> execPlan == NULL ) ;
 }
 * isNull = prm -> isnull ;
 return prm -> value ;
 }