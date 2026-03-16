Datum ExecEvalExprSwitchContext ( ExprState * expression , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Datum retDatum ;
 MemoryContext oldContext ;
 oldContext = MemoryContextSwitchTo ( econtext -> ecxt_per_tuple_memory ) ;
 retDatum = ExecEvalExpr ( expression , econtext , isNull , isDone ) ;
 MemoryContextSwitchTo ( oldContext ) ;
 return retDatum ;
 }