static bool isAssignmentIndirectionExpr ( ExprState * exprstate ) {
 if ( exprstate == NULL ) return false ;
 if ( IsA ( exprstate , FieldStoreState ) ) {
 FieldStore * fstore = ( FieldStore * ) exprstate -> expr ;
 if ( fstore -> arg && IsA ( fstore -> arg , CaseTestExpr ) ) return true ;
 }
 else if ( IsA ( exprstate , ArrayRefExprState ) ) {
 ArrayRef * arrayRef = ( ArrayRef * ) exprstate -> expr ;
 if ( arrayRef -> refexpr && IsA ( arrayRef -> refexpr , CaseTestExpr ) ) return true ;
 }
 return false ;
 }