static Datum ExecEvalGroupingFuncExpr ( GroupingFuncExprState * gstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 int result = 0 ;
 int attnum = 0 ;
 Bitmapset * grouped_cols = gstate -> aggstate -> grouped_cols ;
 ListCell * lc ;
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = false ;
 foreach ( lc , ( gstate -> clauses ) ) {
 attnum = lfirst_int ( lc ) ;
 result = result << 1 ;
 if ( ! bms_is_member ( attnum , grouped_cols ) ) result = result | 1 ;
 }
 return ( Datum ) result ;
 }