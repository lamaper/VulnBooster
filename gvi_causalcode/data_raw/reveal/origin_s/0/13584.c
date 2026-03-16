static bool ExecTargetList ( List * targetlist , TupleDesc tupdesc , ExprContext * econtext , Datum * values , bool * isnull , ExprDoneCond * itemIsDone , ExprDoneCond * isDone ) {
 Form_pg_attribute * att = tupdesc -> attrs ;
 MemoryContext oldContext ;
 ListCell * tl ;
 bool haveDoneSets ;
 oldContext = MemoryContextSwitchTo ( econtext -> ecxt_per_tuple_memory ) ;
 haveDoneSets = false ;
 foreach ( tl , targetlist ) {
 GenericExprState * gstate = ( GenericExprState * ) lfirst ( tl ) ;
 TargetEntry * tle = ( TargetEntry * ) gstate -> xprstate . expr ;
 AttrNumber resind = tle -> resno - 1 ;
 values [ resind ] = ExecEvalExpr ( gstate -> arg , econtext , & isnull [ resind ] , & itemIsDone [ resind ] ) ;
 values [ resind ] = MakeExpandedObjectReadOnly ( values [ resind ] , isnull [ resind ] , att [ resind ] -> attlen ) ;
 if ( itemIsDone [ resind ] != ExprSingleResult ) {
 if ( isDone == NULL ) ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "set-valued function called in context that cannot accept a set" ) ) ) ;
 if ( itemIsDone [ resind ] == ExprMultipleResult ) {
 * isDone = ExprMultipleResult ;
 }
 else {
 haveDoneSets = true ;
 }
 }
 }
 if ( haveDoneSets ) {
 if ( * isDone == ExprSingleResult ) {
 * isDone = ExprEndResult ;
 MemoryContextSwitchTo ( oldContext ) ;
 return false ;
 }
 else {
 foreach ( tl , targetlist ) {
 GenericExprState * gstate = ( GenericExprState * ) lfirst ( tl ) ;
 TargetEntry * tle = ( TargetEntry * ) gstate -> xprstate . expr ;
 AttrNumber resind = tle -> resno - 1 ;
 if ( itemIsDone [ resind ] == ExprEndResult ) {
 values [ resind ] = ExecEvalExpr ( gstate -> arg , econtext , & isnull [ resind ] , & itemIsDone [ resind ] ) ;
 values [ resind ] = MakeExpandedObjectReadOnly ( values [ resind ] , isnull [ resind ] , att [ resind ] -> attlen ) ;
 if ( itemIsDone [ resind ] == ExprEndResult ) {
 * isDone = ExprEndResult ;
 break ;
 }
 }
 }
 if ( * isDone == ExprEndResult ) {
 foreach ( tl , targetlist ) {
 GenericExprState * gstate = ( GenericExprState * ) lfirst ( tl ) ;
 TargetEntry * tle = ( TargetEntry * ) gstate -> xprstate . expr ;
 AttrNumber resind = tle -> resno - 1 ;
 while ( itemIsDone [ resind ] == ExprMultipleResult ) {
 values [ resind ] = ExecEvalExpr ( gstate -> arg , econtext , & isnull [ resind ] , & itemIsDone [ resind ] ) ;
 }
 }
 MemoryContextSwitchTo ( oldContext ) ;
 return false ;
 }
 }
 }
 MemoryContextSwitchTo ( oldContext ) ;
 return true ;
 }