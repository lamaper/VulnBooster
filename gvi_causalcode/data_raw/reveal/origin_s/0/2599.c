double tlist_returns_set_rows ( List * tlist ) {
 double result = 1 ;
 ListCell * lc ;
 foreach ( lc , tlist ) {
 TargetEntry * tle = ( TargetEntry * ) lfirst ( lc ) ;
 double colresult ;
 colresult = expression_returns_set_rows ( ( Node * ) tle -> expr ) ;
 if ( result < colresult ) result = colresult ;
 }
 return result ;
 }