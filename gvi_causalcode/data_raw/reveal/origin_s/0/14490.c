Expr * make_orclause ( List * orclauses ) {
 BoolExpr * expr = makeNode ( BoolExpr ) ;
 expr -> boolop = OR_EXPR ;
 expr -> args = orclauses ;
 expr -> location = - 1 ;
 return ( Expr * ) expr ;
 }