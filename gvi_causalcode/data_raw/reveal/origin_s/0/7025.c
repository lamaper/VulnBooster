static bool contain_context_dependent_node_walker ( Node * node , int * flags ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , CaseTestExpr ) ) return ! ( * flags & CCDN_IN_CASEEXPR ) ;
 if ( IsA ( node , CaseExpr ) ) {
 CaseExpr * caseexpr = ( CaseExpr * ) node ;
 if ( caseexpr -> arg ) {
 int save_flags = * flags ;
 bool res ;
 * flags |= CCDN_IN_CASEEXPR ;
 res = expression_tree_walker ( node , contain_context_dependent_node_walker , ( void * ) flags ) ;
 * flags = save_flags ;
 return res ;
 }
 }
 return expression_tree_walker ( node , contain_context_dependent_node_walker , ( void * ) flags ) ;
 }