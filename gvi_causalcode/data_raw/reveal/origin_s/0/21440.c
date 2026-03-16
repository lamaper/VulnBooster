const char * keydb_get_resource_name ( KEYDB_HANDLE hd ) {
 int idx ;
 const char * s = NULL ;
 if ( ! hd ) return NULL ;
 if ( hd -> found >= 0 && hd -> found < hd -> used ) idx = hd -> found ;
 else if ( hd -> current >= 0 && hd -> current < hd -> used ) idx = hd -> current ;
 else idx = 0 ;
 switch ( hd -> active [ idx ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : s = NULL ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : s = keyring_get_resource_name ( hd -> active [ idx ] . u . kr ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : s = keybox_get_resource_name ( hd -> active [ idx ] . u . kb ) ;
 break ;
 }
 return s ? s : "" ;
 }