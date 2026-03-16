Var * find_forced_null_var ( Node * node ) {
 if ( node == NULL ) return NULL ;
 if ( IsA ( node , NullTest ) ) {
 NullTest * expr = ( NullTest * ) node ;
 if ( expr -> nulltesttype == IS_NULL && ! expr -> argisrow ) {
 Var * var = ( Var * ) expr -> arg ;
 if ( var && IsA ( var , Var ) && var -> varlevelsup == 0 ) return var ;
 }
 }
 else if ( IsA ( node , BooleanTest ) ) {
 BooleanTest * expr = ( BooleanTest * ) node ;
 if ( expr -> booltesttype == IS_UNKNOWN ) {
 Var * var = ( Var * ) expr -> arg ;
 if ( var && IsA ( var , Var ) && var -> varlevelsup == 0 ) return var ;
 }
 }
 return NULL ;
 }