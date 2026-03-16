static Datum ExecEvalArrayRef ( ArrayRefExprState * astate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ArrayRef * arrayRef = ( ArrayRef * ) astate -> xprstate . expr ;
 Datum array_source ;
 bool isAssignment = ( arrayRef -> refassgnexpr != NULL ) ;
 bool eisnull ;
 ListCell * l ;
 int i = 0 , j = 0 ;
 IntArray upper , lower ;
 bool upperProvided [ MAXDIM ] , lowerProvided [ MAXDIM ] ;
 int * lIndex ;
 array_source = ExecEvalExpr ( astate -> refexpr , econtext , isNull , isDone ) ;
 if ( * isNull ) {
 if ( isDone && * isDone == ExprEndResult ) return ( Datum ) NULL ;
 if ( ! isAssignment ) return ( Datum ) NULL ;
 }
 foreach ( l , astate -> refupperindexpr ) {
 ExprState * eltstate = ( ExprState * ) lfirst ( l ) ;
 if ( i >= MAXDIM ) ereport ( ERROR , ( errcode ( ERRCODE_PROGRAM_LIMIT_EXCEEDED ) , errmsg ( "number of array dimensions (%d) exceeds the maximum allowed (%d)" , i + 1 , MAXDIM ) ) ) ;
 if ( eltstate == NULL ) {
 Assert ( astate -> reflowerindexpr != NIL ) ;
 upperProvided [ i ++ ] = false ;
 continue ;
 }
 upperProvided [ i ] = true ;
 upper . indx [ i ++ ] = DatumGetInt32 ( ExecEvalExpr ( eltstate , econtext , & eisnull , NULL ) ) ;
 if ( eisnull ) {
 if ( isAssignment ) ereport ( ERROR , ( errcode ( ERRCODE_NULL_VALUE_NOT_ALLOWED ) , errmsg ( "array subscript in assignment must not be null" ) ) ) ;
 * isNull = true ;
 return ( Datum ) NULL ;
 }
 }
 if ( astate -> reflowerindexpr != NIL ) {
 foreach ( l , astate -> reflowerindexpr ) {
 ExprState * eltstate = ( ExprState * ) lfirst ( l ) ;
 if ( j >= MAXDIM ) ereport ( ERROR , ( errcode ( ERRCODE_PROGRAM_LIMIT_EXCEEDED ) , errmsg ( "number of array dimensions (%d) exceeds the maximum allowed (%d)" , j + 1 , MAXDIM ) ) ) ;
 if ( eltstate == NULL ) {
 lowerProvided [ j ++ ] = false ;
 continue ;
 }
 lowerProvided [ j ] = true ;
 lower . indx [ j ++ ] = DatumGetInt32 ( ExecEvalExpr ( eltstate , econtext , & eisnull , NULL ) ) ;
 if ( eisnull ) {
 if ( isAssignment ) ereport ( ERROR , ( errcode ( ERRCODE_NULL_VALUE_NOT_ALLOWED ) , errmsg ( "array subscript in assignment must not be null" ) ) ) ;
 * isNull = true ;
 return ( Datum ) NULL ;
 }
 }
 if ( i != j ) elog ( ERROR , "upper and lower index lists are not same length" ) ;
 lIndex = lower . indx ;
 }
 else lIndex = NULL ;
 if ( isAssignment ) {
 Datum sourceData ;
 Datum save_datum ;
 bool save_isNull ;
 save_datum = econtext -> caseValue_datum ;
 save_isNull = econtext -> caseValue_isNull ;
 if ( isAssignmentIndirectionExpr ( astate -> refassgnexpr ) ) {
 if ( * isNull ) {
 econtext -> caseValue_datum = ( Datum ) 0 ;
 econtext -> caseValue_isNull = true ;
 }
 else if ( lIndex == NULL ) {
 econtext -> caseValue_datum = array_get_element ( array_source , i , upper . indx , astate -> refattrlength , astate -> refelemlength , astate -> refelembyval , astate -> refelemalign , & econtext -> caseValue_isNull ) ;
 }
 else {
 econtext -> caseValue_datum = array_get_slice ( array_source , i , upper . indx , lower . indx , upperProvided , lowerProvided , astate -> refattrlength , astate -> refelemlength , astate -> refelembyval , astate -> refelemalign ) ;
 econtext -> caseValue_isNull = false ;
 }
 }
 else {
 econtext -> caseValue_datum = ( Datum ) 0 ;
 econtext -> caseValue_isNull = true ;
 }
 sourceData = ExecEvalExpr ( astate -> refassgnexpr , econtext , & eisnull , NULL ) ;
 econtext -> caseValue_datum = save_datum ;
 econtext -> caseValue_isNull = save_isNull ;
 if ( astate -> refattrlength > 0 ) if ( eisnull || * isNull ) return array_source ;
 if ( * isNull ) {
 array_source = PointerGetDatum ( construct_empty_array ( arrayRef -> refelemtype ) ) ;
 * isNull = false ;
 }
 if ( lIndex == NULL ) return array_set_element ( array_source , i , upper . indx , sourceData , eisnull , astate -> refattrlength , astate -> refelemlength , astate -> refelembyval , astate -> refelemalign ) ;
 else return array_set_slice ( array_source , i , upper . indx , lower . indx , upperProvided , lowerProvided , sourceData , eisnull , astate -> refattrlength , astate -> refelemlength , astate -> refelembyval , astate -> refelemalign ) ;
 }
 if ( lIndex == NULL ) return array_get_element ( array_source , i , upper . indx , astate -> refattrlength , astate -> refelemlength , astate -> refelembyval , astate -> refelemalign , isNull ) ;
 else return array_get_slice ( array_source , i , upper . indx , lower . indx , upperProvided , lowerProvided , astate -> refattrlength , astate -> refelemlength , astate -> refelembyval , astate -> refelemalign ) ;
 }