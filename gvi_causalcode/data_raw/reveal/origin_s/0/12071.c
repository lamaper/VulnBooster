bool not_clause ( Node * clause ) {
 return ( clause != NULL && IsA ( clause , BoolExpr ) && ( ( BoolExpr * ) clause ) -> boolop == NOT_EXPR ) ;
 }