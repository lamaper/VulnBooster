void keydb_release ( KEYDB_HANDLE hd ) {
 int i ;
 if ( ! hd ) return ;
 assert ( active_handles > 0 ) ;
 active_handles -- ;
 unlock_all ( hd ) ;
 for ( i = 0 ;
 i < hd -> used ;
 i ++ ) {
 switch ( hd -> active [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : keyring_release ( hd -> active [ i ] . u . kr ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : keybox_release ( hd -> active [ i ] . u . kb ) ;
 break ;
 }
 }
 xfree ( hd ) ;
 }