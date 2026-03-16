static Datum ExecEvalRow ( RowExprState * rstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 HeapTuple tuple ;
 Datum * values ;
 bool * isnull ;
 int natts ;
 ListCell * arg ;
 int i ;
 * isNull = false ;
 if ( isDone ) * isDone = ExprSingleResult ;
 natts = rstate -> tupdesc -> natts ;
 values = ( Datum * ) palloc0 ( natts * sizeof ( Datum ) ) ;
 isnull = ( bool * ) palloc ( natts * sizeof ( bool ) ) ;
 memset ( isnull , true , natts * sizeof ( bool ) ) ;
 i = 0 ;
 foreach ( arg , rstate -> args ) {
 ExprState * e = ( ExprState * ) lfirst ( arg ) ;
 values [ i ] = ExecEvalExpr ( e , econtext , & isnull [ i ] , NULL ) ;
 i ++ ;
 }
 tuple = heap_form_tuple ( rstate -> tupdesc , values , isnull ) ;
 pfree ( values ) ;
 pfree ( isnull ) ;
 return HeapTupleGetDatum ( tuple ) ;
 }