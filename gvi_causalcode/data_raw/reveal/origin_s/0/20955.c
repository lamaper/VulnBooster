static Relids find_nonnullable_rels_walker ( Node * node , bool top_level ) {
 Relids result = NULL ;
 ListCell * l ;
 if ( node == NULL ) return NULL ;
 if ( IsA ( node , Var ) ) {
 Var * var = ( Var * ) node ;
 if ( var -> varlevelsup == 0 ) result = bms_make_singleton ( var -> varno ) ;
 }
 else if ( IsA ( node , List ) ) {
 foreach ( l , ( List * ) node ) {
 result = bms_join ( result , find_nonnullable_rels_walker ( lfirst ( l ) , top_level ) ) ;
 }
 }
 else if ( IsA ( node , FuncExpr ) ) {
 FuncExpr * expr = ( FuncExpr * ) node ;
 if ( func_strict ( expr -> funcid ) ) result = find_nonnullable_rels_walker ( ( Node * ) expr -> args , false ) ;
 }
 else if ( IsA ( node , OpExpr ) ) {
 OpExpr * expr = ( OpExpr * ) node ;
 set_opfuncid ( expr ) ;
 if ( func_strict ( expr -> opfuncid ) ) result = find_nonnullable_rels_walker ( ( Node * ) expr -> args , false ) ;
 }
 else if ( IsA ( node , ScalarArrayOpExpr ) ) {
 ScalarArrayOpExpr * expr = ( ScalarArrayOpExpr * ) node ;
 if ( is_strict_saop ( expr , true ) ) result = find_nonnullable_rels_walker ( ( Node * ) expr -> args , false ) ;
 }
 else if ( IsA ( node , BoolExpr ) ) {
 BoolExpr * expr = ( BoolExpr * ) node ;
 switch ( expr -> boolop ) {
 case AND_EXPR : if ( top_level ) {
 result = find_nonnullable_rels_walker ( ( Node * ) expr -> args , top_level ) ;
 break ;
 }
 case OR_EXPR : foreach ( l , expr -> args ) {
 Relids subresult ;
 subresult = find_nonnullable_rels_walker ( lfirst ( l ) , top_level ) ;
 if ( result == NULL ) result = subresult ;
 else result = bms_int_members ( result , subresult ) ;
 if ( bms_is_empty ( result ) ) break ;
 }
 break ;
 case NOT_EXPR : result = find_nonnullable_rels_walker ( ( Node * ) expr -> args , false ) ;
 break ;
 default : elog ( ERROR , "unrecognized boolop: %d" , ( int ) expr -> boolop ) ;
 break ;
 }
 }
 else if ( IsA ( node , RelabelType ) ) {
 RelabelType * expr = ( RelabelType * ) node ;
 result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , top_level ) ;
 }
 else if ( IsA ( node , CoerceViaIO ) ) {
 CoerceViaIO * expr = ( CoerceViaIO * ) node ;
 result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , top_level ) ;
 }
 else if ( IsA ( node , ArrayCoerceExpr ) ) {
 ArrayCoerceExpr * expr = ( ArrayCoerceExpr * ) node ;
 result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , top_level ) ;
 }
 else if ( IsA ( node , ConvertRowtypeExpr ) ) {
 ConvertRowtypeExpr * expr = ( ConvertRowtypeExpr * ) node ;
 result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , top_level ) ;
 }
 else if ( IsA ( node , CollateExpr ) ) {
 CollateExpr * expr = ( CollateExpr * ) node ;
 result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , top_level ) ;
 }
 else if ( IsA ( node , NullTest ) ) {
 NullTest * expr = ( NullTest * ) node ;
 if ( top_level && expr -> nulltesttype == IS_NOT_NULL && ! expr -> argisrow ) result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , false ) ;
 }
 else if ( IsA ( node , BooleanTest ) ) {
 BooleanTest * expr = ( BooleanTest * ) node ;
 if ( top_level && ( expr -> booltesttype == IS_TRUE || expr -> booltesttype == IS_FALSE || expr -> booltesttype == IS_NOT_UNKNOWN ) ) result = find_nonnullable_rels_walker ( ( Node * ) expr -> arg , false ) ;
 }
 else if ( IsA ( node , PlaceHolderVar ) ) {
 PlaceHolderVar * phv = ( PlaceHolderVar * ) node ;
 result = find_nonnullable_rels_walker ( ( Node * ) phv -> phexpr , top_level ) ;
 }
 return result ;
 }