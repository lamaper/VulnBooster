static Datum ExecEvalOper ( FuncExprState * fcache , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 OpExpr * op = ( OpExpr * ) fcache -> xprstate . expr ;
 init_fcache ( op -> opfuncid , op -> inputcollid , fcache , econtext -> ecxt_per_query_memory , true ) ;
 if ( fcache -> func . fn_retset || expression_returns_set ( ( Node * ) op -> args ) ) {
 fcache -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecMakeFunctionResult ;
 return ExecMakeFunctionResult ( fcache , econtext , isNull , isDone ) ;
 }
 else {
 fcache -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecMakeFunctionResultNoSets ;
 return ExecMakeFunctionResultNoSets ( fcache , econtext , isNull , isDone ) ;
 }
 }