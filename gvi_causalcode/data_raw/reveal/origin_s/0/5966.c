ExprState * ExecPrepareExpr ( Expr * node , EState * estate ) {
 ExprState * result ;
 MemoryContext oldcontext ;
 oldcontext = MemoryContextSwitchTo ( estate -> es_query_cxt ) ;
 node = expression_planner ( node ) ;
 result = ExecInitExpr ( node , NULL ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 return result ;
 }