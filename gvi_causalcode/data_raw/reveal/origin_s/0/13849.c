static void ShutdownFuncExpr ( Datum arg ) {
 FuncExprState * fcache = ( FuncExprState * ) DatumGetPointer ( arg ) ;
 if ( fcache -> funcResultSlot ) ExecClearTuple ( fcache -> funcResultSlot ) ;
 if ( fcache -> funcResultStore ) tuplestore_end ( fcache -> funcResultStore ) ;
 fcache -> funcResultStore = NULL ;
 fcache -> setArgsValid = false ;
 fcache -> shutdown_reg = false ;
 }