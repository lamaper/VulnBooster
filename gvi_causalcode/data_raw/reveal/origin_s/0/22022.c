bool get_restriction_variable ( PlannerInfo * root , List * args , int varRelid , VariableStatData * vardata , Node * * other , bool * varonleft ) {
 Node * left , * right ;
 VariableStatData rdata ;
 if ( list_length ( args ) != 2 ) return false ;
 left = ( Node * ) linitial ( args ) ;
 right = ( Node * ) lsecond ( args ) ;
 examine_variable ( root , left , varRelid , vardata ) ;
 examine_variable ( root , right , varRelid , & rdata ) ;
 if ( vardata -> rel && rdata . rel == NULL ) {
 * varonleft = true ;
 * other = estimate_expression_value ( root , rdata . var ) ;
 return true ;
 }
 if ( vardata -> rel == NULL && rdata . rel ) {
 * varonleft = false ;
 * other = estimate_expression_value ( root , vardata -> var ) ;
 * vardata = rdata ;
 return true ;
 }
 ReleaseVariableStats ( * vardata ) ;
 ReleaseVariableStats ( rdata ) ;
 return false ;
 }