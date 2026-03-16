static Datum ExecEvalParamExtern ( ExprState * exprstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Param * expression = ( Param * ) exprstate -> expr ;
 int thisParamId = expression -> paramid ;
 ParamListInfo paramInfo = econtext -> ecxt_param_list_info ;
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( paramInfo && thisParamId > 0 && thisParamId <= paramInfo -> numParams ) {
 ParamExternData * prm = & paramInfo -> params [ thisParamId - 1 ] ;
 if ( ! OidIsValid ( prm -> ptype ) && paramInfo -> paramFetch != NULL ) ( * paramInfo -> paramFetch ) ( paramInfo , thisParamId ) ;
 if ( OidIsValid ( prm -> ptype ) ) {
 if ( prm -> ptype != expression -> paramtype ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "type of parameter %d (%s) does not match that when preparing the plan (%s)" , thisParamId , format_type_be ( prm -> ptype ) , format_type_be ( expression -> paramtype ) ) ) ) ;
 * isNull = prm -> isnull ;
 return prm -> value ;
 }
 }
 ereport ( ERROR , ( errcode ( ERRCODE_UNDEFINED_OBJECT ) , errmsg ( "no value found for parameter %d" , thisParamId ) ) ) ;
 return ( Datum ) 0 ;
 }