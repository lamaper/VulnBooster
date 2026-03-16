bool ExecQual ( List * qual , ExprContext * econtext , bool resultForNull ) {
 bool result ;
 MemoryContext oldContext ;
 ListCell * l ;
 EV_printf ( "ExecQual: qual is " ) ;
 EV_nodeDisplay ( qual ) ;
 EV_printf ( "\n" ) ;
 oldContext = MemoryContextSwitchTo ( econtext -> ecxt_per_tuple_memory ) ;
 result = true ;
 foreach ( l , qual ) {
 ExprState * clause = ( ExprState * ) lfirst ( l ) ;
 Datum expr_value ;
 bool isNull ;
 expr_value = ExecEvalExpr ( clause , econtext , & isNull , NULL ) ;
 if ( isNull ) {
 if ( resultForNull == false ) {
 result = false ;
 break ;
 }
 }
 else {
 if ( ! DatumGetBool ( expr_value ) ) {
 result = false ;
 break ;
 }
 }
 }
 MemoryContextSwitchTo ( oldContext ) ;
 return result ;
 }