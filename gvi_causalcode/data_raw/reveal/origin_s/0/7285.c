static bool tlist_matches_coltypelist ( List * tlist , List * coltypelist ) {
 ListCell * tlistitem ;
 ListCell * clistitem ;
 clistitem = list_head ( coltypelist ) ;
 foreach ( tlistitem , tlist ) {
 TargetEntry * tle = ( TargetEntry * ) lfirst ( tlistitem ) ;
 Oid coltype ;
 if ( tle -> resjunk ) continue ;
 if ( clistitem == NULL ) return false ;
 coltype = lfirst_oid ( clistitem ) ;
 clistitem = lnext ( clistitem ) ;
 if ( exprType ( ( Node * ) tle -> expr ) != coltype ) return false ;
 }
 if ( clistitem != NULL ) return false ;
 return true ;
 }