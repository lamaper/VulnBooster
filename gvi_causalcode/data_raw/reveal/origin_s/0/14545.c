static Datum ExecEvalMinMax ( MinMaxExprState * minmaxExpr , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Datum result = ( Datum ) 0 ;
 MinMaxExpr * minmax = ( MinMaxExpr * ) minmaxExpr -> xprstate . expr ;
 Oid collation = minmax -> inputcollid ;
 MinMaxOp op = minmax -> op ;
 FunctionCallInfoData locfcinfo ;
 ListCell * arg ;
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = true ;
 InitFunctionCallInfoData ( locfcinfo , & minmaxExpr -> cfunc , 2 , collation , NULL , NULL ) ;
 locfcinfo . argnull [ 0 ] = false ;
 locfcinfo . argnull [ 1 ] = false ;
 foreach ( arg , minmaxExpr -> args ) {
 ExprState * e = ( ExprState * ) lfirst ( arg ) ;
 Datum value ;
 bool valueIsNull ;
 int32 cmpresult ;
 value = ExecEvalExpr ( e , econtext , & valueIsNull , NULL ) ;
 if ( valueIsNull ) continue ;
 if ( * isNull ) {
 result = value ;
 * isNull = false ;
 }
 else {
 locfcinfo . arg [ 0 ] = result ;
 locfcinfo . arg [ 1 ] = value ;
 locfcinfo . isnull = false ;
 cmpresult = DatumGetInt32 ( FunctionCallInvoke ( & locfcinfo ) ) ;
 if ( locfcinfo . isnull ) continue ;
 if ( cmpresult > 0 && op == IS_LEAST ) result = value ;
 else if ( cmpresult < 0 && op == IS_GREATEST ) result = value ;
 }
 }
 return result ;
 }