Expr * make_notclause ( Expr * notclause ) {
 BoolExpr * expr = makeNode ( BoolExpr ) ;
 expr -> boolop = NOT_EXPR ;
 expr -> args = list_make1 ( notclause ) ;
 expr -> location = - 1 ;
 return ( Expr * ) expr ;
 }