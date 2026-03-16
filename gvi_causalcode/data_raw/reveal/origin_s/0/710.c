static Datum ExecEvalCoalesce ( CoalesceExprState * coalesceExpr , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ListCell * arg ;
 if ( isDone ) * isDone = ExprSingleResult ;
 foreach ( arg , coalesceExpr -> args ) {
 ExprState * e = ( ExprState * ) lfirst ( arg ) ;
 Datum value ;
 value = ExecEvalExpr ( e , econtext , isNull , NULL ) ;
 if ( ! * isNull ) return value ;
 }
 * isNull = true ;
 return ( Datum ) 0 ;
 }