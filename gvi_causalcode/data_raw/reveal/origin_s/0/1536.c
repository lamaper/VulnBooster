Node * get_leftop ( const Expr * clause ) {
 const OpExpr * expr = ( const OpExpr * ) clause ;
 if ( expr -> args != NIL ) return linitial ( expr -> args ) ;
 else return NULL ;
 }