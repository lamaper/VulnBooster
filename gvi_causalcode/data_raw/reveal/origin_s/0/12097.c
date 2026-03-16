KEYDB_HANDLE keydb_new ( void ) {
 KEYDB_HANDLE hd ;
 int i , j ;
 if ( DBG_CLOCK ) log_clock ( "keydb_new" ) ;
 hd = xmalloc_clear ( sizeof * hd ) ;
 hd -> found = - 1 ;
 assert ( used_resources <= MAX_KEYDB_RESOURCES ) ;
 for ( i = j = 0 ;
 i < used_resources ;
 i ++ ) {
 switch ( all_resources [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : hd -> active [ j ] . type = all_resources [ i ] . type ;
 hd -> active [ j ] . token = all_resources [ i ] . token ;
 hd -> active [ j ] . u . kr = keyring_new ( all_resources [ i ] . token ) ;
 if ( ! hd -> active [ j ] . u . kr ) {
 xfree ( hd ) ;
 return NULL ;
 }
 j ++ ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : hd -> active [ j ] . type = all_resources [ i ] . type ;
 hd -> active [ j ] . token = all_resources [ i ] . token ;
 hd -> active [ j ] . u . kb = keybox_new_openpgp ( all_resources [ i ] . token , 0 ) ;
 if ( ! hd -> active [ j ] . u . kb ) {
 xfree ( hd ) ;
 return NULL ;
 }
 j ++ ;
 break ;
 }
 }
 hd -> used = j ;
 active_handles ++ ;
 return hd ;
 }