Expr * make_andclause ( List * andclauses ) {
 BoolExpr * expr = makeNode ( BoolExpr ) ;
 expr -> boolop = AND_EXPR ;
 expr -> args = andclauses ;
 expr -> location = - 1 ;
 return ( Expr * ) expr ;
 }