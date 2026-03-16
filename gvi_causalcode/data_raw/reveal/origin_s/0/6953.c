static Datum ExecEvalScalarVar ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Var * variable = ( Var * ) exprstate -> expr ;
 TupleTableSlot * slot ;
 AttrNumber attnum ;
 if ( isDone ) * isDone = ExprSingleResult ;
 switch ( variable -> varno ) {
 case INNER_VAR : slot = econtext -> ecxt_innertuple ;
 break ;
 case OUTER_VAR : slot = econtext -> ecxt_outertuple ;
 break ;
 default : slot = econtext -> ecxt_scantuple ;
 break ;
 }
 attnum = variable -> varattno ;
 Assert ( attnum != InvalidAttrNumber ) ;
 if ( attnum > 0 ) {
 TupleDesc slot_tupdesc = slot -> tts_tupleDescriptor ;
 Form_pg_attribute attr ;
 if ( attnum > slot_tupdesc -> natts ) elog ( ERROR , "attribute number %d exceeds number of columns %d" , attnum , slot_tupdesc -> natts ) ;
 attr = slot_tupdesc -> attrs [ attnum - 1 ] ;
 if ( ! attr -> attisdropped ) {
 if ( variable -> vartype != attr -> atttypid ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "attribute %d has wrong type" , attnum ) , errdetail ( "Table has type %s, but query expects %s." , format_type_be ( attr -> atttypid ) , format_type_be ( variable -> vartype ) ) ) ) ;
 }
 }
 exprstate -> evalfunc = ExecEvalScalarVarFast ;
 return slot_getattr ( slot , attnum , isNull ) ;
 }