static Datum ExecEvalRowCompare ( RowCompareExprState * rstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 bool result ;
 RowCompareType rctype = ( ( RowCompareExpr * ) rstate -> xprstate . expr ) -> rctype ;
 int32 cmpresult = 0 ;
 ListCell * l ;
 ListCell * r ;
 int i ;
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = true ;
 i = 0 ;
 forboth ( l , rstate -> largs , r , rstate -> rargs ) {
 ExprState * le = ( ExprState * ) lfirst ( l ) ;
 ExprState * re = ( ExprState * ) lfirst ( r ) ;
 FunctionCallInfoData locfcinfo ;
 InitFunctionCallInfoData ( locfcinfo , & ( rstate -> funcs [ i ] ) , 2 , rstate -> collations [ i ] , NULL , NULL ) ;
 locfcinfo . arg [ 0 ] = ExecEvalExpr ( le , econtext , & locfcinfo . argnull [ 0 ] , NULL ) ;
 locfcinfo . arg [ 1 ] = ExecEvalExpr ( re , econtext , & locfcinfo . argnull [ 1 ] , NULL ) ;
 if ( rstate -> funcs [ i ] . fn_strict && ( locfcinfo . argnull [ 0 ] || locfcinfo . argnull [ 1 ] ) ) return ( Datum ) 0 ;
 locfcinfo . isnull = false ;
 cmpresult = DatumGetInt32 ( FunctionCallInvoke ( & locfcinfo ) ) ;
 if ( locfcinfo . isnull ) return ( Datum ) 0 ;
 if ( cmpresult != 0 ) break ;
 i ++ ;
 }
 switch ( rctype ) {
 case ROWCOMPARE_LT : result = ( cmpresult < 0 ) ;
 break ;
 case ROWCOMPARE_LE : result = ( cmpresult <= 0 ) ;
 break ;
 case ROWCOMPARE_GE : result = ( cmpresult >= 0 ) ;
 break ;
 case ROWCOMPARE_GT : result = ( cmpresult > 0 ) ;
 break ;
 default : elog ( ERROR , "unrecognized RowCompareType: %d" , ( int ) rctype ) ;
 result = 0 ;
 break ;
 }
 * isNull = false ;
 return BoolGetDatum ( result ) ;
 }