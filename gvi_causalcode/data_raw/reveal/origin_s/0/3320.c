int ExecCleanTargetListLength ( List * targetlist ) {
 int len = 0 ;
 ListCell * tl ;
 foreach ( tl , targetlist ) {
 TargetEntry * curTle = ( TargetEntry * ) lfirst ( tl ) ;
 Assert ( IsA ( curTle , TargetEntry ) ) ;
 if ( ! curTle -> resjunk ) len ++ ;
 }
 return len ;
 }