void xmlListReverseWalk ( xmlListPtr l , xmlListWalker walker , const void * user ) {
 xmlLinkPtr lk ;
 if ( ( l == NULL ) || ( walker == NULL ) ) return ;
 for ( lk = l -> sentinel -> prev ;
 lk != l -> sentinel ;
 lk = lk -> prev ) {
 if ( ( walker ( lk -> data , user ) ) == 0 ) break ;
 }
 }