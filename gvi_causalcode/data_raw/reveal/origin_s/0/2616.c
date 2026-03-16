int keyring_lock ( KEYRING_HANDLE hd , int yes ) {
 KR_NAME kr ;
 int rc = 0 ;
 ( void ) hd ;
 if ( yes ) {
 for ( kr = kr_names ;
 kr ;
 kr = kr -> next ) {
 if ( ! keyring_is_writable ( kr ) ) continue ;
 if ( ! kr -> lockhd ) {
 kr -> lockhd = dotlock_create ( kr -> fname , 0 ) ;
 if ( ! kr -> lockhd ) {
 log_info ( "can't allocate lock for '%s'\n" , kr -> fname ) ;
 rc = GPG_ERR_GENERAL ;
 }
 }
 }
 if ( rc ) return rc ;
 for ( kr = kr_names ;
 kr ;
 kr = kr -> next ) {
 if ( ! keyring_is_writable ( kr ) ) continue ;
 if ( kr -> is_locked ) ;
 else if ( dotlock_take ( kr -> lockhd , - 1 ) ) {
 log_info ( "can't lock '%s'\n" , kr -> fname ) ;
 rc = GPG_ERR_GENERAL ;
 }
 else kr -> is_locked = 1 ;
 }
 }
 if ( rc || ! yes ) {
 for ( kr = kr_names ;
 kr ;
 kr = kr -> next ) {
 if ( ! keyring_is_writable ( kr ) ) continue ;
 if ( ! kr -> is_locked ) ;
 else if ( dotlock_release ( kr -> lockhd ) ) log_info ( "can't unlock '%s'\n" , kr -> fname ) ;
 else kr -> is_locked = 0 ;
 }
 }
 return rc ;
 }