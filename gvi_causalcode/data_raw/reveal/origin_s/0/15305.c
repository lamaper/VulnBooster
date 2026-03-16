bool and_clause ( Node * clause ) {
 return ( clause != NULL && IsA ( clause , BoolExpr ) && ( ( BoolExpr * ) clause ) -> boolop == AND_EXPR ) ;
 }