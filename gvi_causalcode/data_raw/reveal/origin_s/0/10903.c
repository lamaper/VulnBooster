static Datum ExecEvalFunc ( FuncExprState * fcache , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 FuncExpr * func = ( FuncExpr * ) fcache -> xprstate . expr ;
 init_fcache ( func -> funcid , func -> inputcollid , fcache , econtext -> ecxt_per_query_memory , true ) ;
 if ( fcache -> func . fn_retset || expression_returns_set ( ( Node * ) func -> args ) ) {
 fcache -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecMakeFunctionResult ;
 return ExecMakeFunctionResult ( fcache , econtext , isNull , isDone ) ;
 }
 else {
 fcache -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecMakeFunctionResultNoSets ;
 return ExecMakeFunctionResultNoSets ( fcache , econtext , isNull , isDone ) ;
 }
 }