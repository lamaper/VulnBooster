void xmlListWalk ( xmlListPtr l , xmlListWalker walker , const void * user ) {
 xmlLinkPtr lk ;
 if ( ( l == NULL ) || ( walker == NULL ) ) return ;
 for ( lk = l -> sentinel -> next ;
 lk != l -> sentinel ;
 lk = lk -> next ) {
 if ( ( walker ( lk -> data , user ) ) == 0 ) break ;
 }
 }