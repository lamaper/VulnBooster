static int lock_all ( KEYDB_HANDLE hd ) {
 int i , rc = 0 ;
 for ( i = 0 ;
 ! rc && i < hd -> used ;
 i ++ ) {
 switch ( hd -> active [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : rc = keyring_lock ( hd -> active [ i ] . u . kr , 1 ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : rc = keybox_lock ( hd -> active [ i ] . u . kb , 1 ) ;
 break ;
 }
 }
 if ( rc ) {
 for ( i -- ;
 i >= 0 ;
 i -- ) {
 switch ( hd -> active [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : keyring_lock ( hd -> active [ i ] . u . kr , 0 ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : rc = keybox_lock ( hd -> active [ i ] . u . kb , 0 ) ;
 break ;
 }
 }
 }
 else hd -> locked = 1 ;
 return rc ;
 }