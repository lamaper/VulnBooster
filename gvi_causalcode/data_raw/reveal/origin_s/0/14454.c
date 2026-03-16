static bool contain_nonstrict_functions_walker ( Node * node , void * context ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , Aggref ) ) {
 return true ;
 }
 if ( IsA ( node , GroupingFunc ) ) {
 return true ;
 }
 if ( IsA ( node , WindowFunc ) ) {
 return true ;
 }
 if ( IsA ( node , ArrayRef ) ) {
 if ( ( ( ArrayRef * ) node ) -> refassgnexpr != NULL ) return true ;
 }
 if ( IsA ( node , DistinctExpr ) ) {
 return true ;
 }
 if ( IsA ( node , NullIfExpr ) ) {
 return true ;
 }
 if ( IsA ( node , BoolExpr ) ) {
 BoolExpr * expr = ( BoolExpr * ) node ;
 switch ( expr -> boolop ) {
 case AND_EXPR : case OR_EXPR : return true ;
 default : break ;
 }
 }
 if ( IsA ( node , SubLink ) ) {
 return true ;
 }
 if ( IsA ( node , SubPlan ) ) return true ;
 if ( IsA ( node , AlternativeSubPlan ) ) return true ;
 if ( IsA ( node , FieldStore ) ) return true ;
 if ( IsA ( node , CaseExpr ) ) return true ;
 if ( IsA ( node , ArrayExpr ) ) return true ;
 if ( IsA ( node , RowExpr ) ) return true ;
 if ( IsA ( node , RowCompareExpr ) ) return true ;
 if ( IsA ( node , CoalesceExpr ) ) return true ;
 if ( IsA ( node , MinMaxExpr ) ) return true ;
 if ( IsA ( node , XmlExpr ) ) return true ;
 if ( IsA ( node , NullTest ) ) return true ;
 if ( IsA ( node , BooleanTest ) ) return true ;
 if ( ! IsA ( node , ArrayCoerceExpr ) && check_functions_in_node ( node , contain_nonstrict_functions_checker , context ) ) return true ;
 return expression_tree_walker ( node , contain_nonstrict_functions_walker , context ) ;
 }