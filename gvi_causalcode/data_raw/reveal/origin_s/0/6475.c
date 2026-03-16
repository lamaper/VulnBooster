static int prepare_search ( KEYRING_HANDLE hd ) {
 if ( hd -> current . error ) {
 if ( gpg_err_code ( hd -> current . error ) == GPG_ERR_LEGACY_KEY ) hd -> current . error = 0 ;
 else return hd -> current . error ;
 }
 if ( hd -> current . kr && ! hd -> current . eof ) {
 if ( ! hd -> current . iobuf ) return GPG_ERR_GENERAL ;
 return 0 ;
 }
 if ( ! hd -> current . kr && hd -> current . eof ) return - 1 ;
 if ( ! hd -> current . kr ) {
 hd -> current . kr = hd -> resource ;
 if ( ! hd -> current . kr ) {
 hd -> current . eof = 1 ;
 return - 1 ;
 }
 assert ( ! hd -> current . iobuf ) ;
 }
 else {
 iobuf_close ( hd -> current . iobuf ) ;
 hd -> current . iobuf = NULL ;
 hd -> current . kr = NULL ;
 hd -> current . eof = 1 ;
 return - 1 ;
 }
 hd -> current . eof = 0 ;
 hd -> current . iobuf = iobuf_open ( hd -> current . kr -> fname ) ;
 if ( ! hd -> current . iobuf ) {
 hd -> current . error = gpg_error_from_syserror ( ) ;
 log_error ( _ ( "can't open '%s'\n" ) , hd -> current . kr -> fname ) ;
 return hd -> current . error ;
 }
 return 0 ;
 }