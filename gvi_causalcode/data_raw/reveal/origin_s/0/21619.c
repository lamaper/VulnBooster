static void unlock_all ( KEYDB_HANDLE hd ) {
 int i ;
 if ( ! hd -> locked ) return ;
 for ( i = hd -> used - 1 ;
 i >= 0 ;
 i -- ) {
 switch ( hd -> active [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : keyring_lock ( hd -> active [ i ] . u . kr , 0 ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : keybox_lock ( hd -> active [ i ] . u . kb , 0 ) ;
 break ;
 }
 }
 hd -> locked = 0 ;
 }