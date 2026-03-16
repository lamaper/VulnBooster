TupleTableSlot * ExecProject ( ProjectionInfo * projInfo , ExprDoneCond * isDone ) {
 TupleTableSlot * slot ;
 ExprContext * econtext ;
 int numSimpleVars ;
 Assert ( projInfo != NULL ) ;
 slot = projInfo -> pi_slot ;
 econtext = projInfo -> pi_exprContext ;
 if ( isDone ) * isDone = ExprSingleResult ;
 ExecClearTuple ( slot ) ;
 if ( projInfo -> pi_lastInnerVar > 0 ) slot_getsomeattrs ( econtext -> ecxt_innertuple , projInfo -> pi_lastInnerVar ) ;
 if ( projInfo -> pi_lastOuterVar > 0 ) slot_getsomeattrs ( econtext -> ecxt_outertuple , projInfo -> pi_lastOuterVar ) ;
 if ( projInfo -> pi_lastScanVar > 0 ) slot_getsomeattrs ( econtext -> ecxt_scantuple , projInfo -> pi_lastScanVar ) ;
 numSimpleVars = projInfo -> pi_numSimpleVars ;
 if ( numSimpleVars > 0 ) {
 Datum * values = slot -> tts_values ;
 bool * isnull = slot -> tts_isnull ;
 int * varSlotOffsets = projInfo -> pi_varSlotOffsets ;
 int * varNumbers = projInfo -> pi_varNumbers ;
 int i ;
 if ( projInfo -> pi_directMap ) {
 for ( i = 0 ;
 i < numSimpleVars ;
 i ++ ) {
 char * slotptr = ( ( char * ) econtext ) + varSlotOffsets [ i ] ;
 TupleTableSlot * varSlot = * ( ( TupleTableSlot * * ) slotptr ) ;
 int varNumber = varNumbers [ i ] - 1 ;
 values [ i ] = varSlot -> tts_values [ varNumber ] ;
 isnull [ i ] = varSlot -> tts_isnull [ varNumber ] ;
 }
 }
 else {
 int * varOutputCols = projInfo -> pi_varOutputCols ;
 for ( i = 0 ;
 i < numSimpleVars ;
 i ++ ) {
 char * slotptr = ( ( char * ) econtext ) + varSlotOffsets [ i ] ;
 TupleTableSlot * varSlot = * ( ( TupleTableSlot * * ) slotptr ) ;
 int varNumber = varNumbers [ i ] - 1 ;
 int varOutputCol = varOutputCols [ i ] - 1 ;
 values [ varOutputCol ] = varSlot -> tts_values [ varNumber ] ;
 isnull [ varOutputCol ] = varSlot -> tts_isnull [ varNumber ] ;
 }
 }
 }
 if ( projInfo -> pi_targetlist ) {
 if ( ! ExecTargetList ( projInfo -> pi_targetlist , slot -> tts_tupleDescriptor , econtext , slot -> tts_values , slot -> tts_isnull , projInfo -> pi_itemIsDone , isDone ) ) return slot ;
 }
 return ExecStoreVirtualTuple ( slot ) ;
 }