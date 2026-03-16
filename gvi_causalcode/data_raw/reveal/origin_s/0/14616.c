Expr * get_notclausearg ( Expr * notclause ) {
 return linitial ( ( ( BoolExpr * ) notclause ) -> args ) ;
 }