bool or_clause ( Node * clause ) {
 return ( clause != NULL && IsA ( clause , BoolExpr ) && ( ( BoolExpr * ) clause ) -> boolop == OR_EXPR ) ;
 }