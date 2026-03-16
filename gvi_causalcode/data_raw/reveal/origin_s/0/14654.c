static bool contain_agg_clause_walker ( Node * node , void * context ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , Aggref ) ) {
 Assert ( ( ( Aggref * ) node ) -> agglevelsup == 0 ) ;
 return true ;
 }
 if ( IsA ( node , GroupingFunc ) ) {
 Assert ( ( ( GroupingFunc * ) node ) -> agglevelsup == 0 ) ;
 return true ;
 }
 Assert ( ! IsA ( node , SubLink ) ) ;
 return expression_tree_walker ( node , contain_agg_clause_walker , context ) ;
 }