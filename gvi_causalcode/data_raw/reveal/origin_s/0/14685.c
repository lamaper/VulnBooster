List * find_forced_null_vars ( Node * node ) {
 List * result = NIL ;
 Var * var ;
 ListCell * l ;
 if ( node == NULL ) return NIL ;
 var = find_forced_null_var ( node ) ;
 if ( var ) {
 result = list_make1 ( var ) ;
 }
 else if ( IsA ( node , List ) ) {
 foreach ( l , ( List * ) node ) {
 result = list_concat ( result , find_forced_null_vars ( lfirst ( l ) ) ) ;
 }
 }
 else if ( IsA ( node , BoolExpr ) ) {
 BoolExpr * expr = ( BoolExpr * ) node ;
 if ( expr -> boolop == AND_EXPR ) {
 result = find_forced_null_vars ( ( Node * ) expr -> args ) ;
 }
 }
 return result ;
 }