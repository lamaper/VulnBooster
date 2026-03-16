Expr * make_ands_explicit ( List * andclauses ) {
 if ( andclauses == NIL ) return ( Expr * ) makeBoolConst ( true , false ) ;
 else if ( list_length ( andclauses ) == 1 ) return ( Expr * ) linitial ( andclauses ) ;
 else return make_andclause ( andclauses ) ;
 }