int authreadkeys ( const char * file ) {
 FILE * fp ;
 char * line ;
 char * token ;
 keyid_t keyno ;
 int keytype ;
 char buf [ 512 ] ;
 u_char keystr [ 32 ] ;
 size_t len ;
 size_t j ;
 size_t nerr ;
 fp = fopen ( file , "r" ) ;
 if ( fp == NULL ) {
 msyslog ( LOG_ERR , "authreadkeys: file %s: %m" , file ) ;
 return ( 0 ) ;
 }
 INIT_SSL ( ) ;
 auth_delkeys ( ) ;
 nerr = 0 ;
 while ( ( line = fgets ( buf , sizeof buf , fp ) ) != NULL ) {
 if ( nerr > nerr_maxlimit ) break ;
 token = nexttok ( & line ) ;
 if ( token == NULL ) continue ;
 keyno = atoi ( token ) ;
 if ( keyno == 0 ) {
 log_maybe ( & nerr , "authreadkeys: cannot change key %s" , token ) ;
 continue ;
 }
 if ( keyno > NTP_MAXKEY ) {
 log_maybe ( & nerr , "authreadkeys: key %s > %d reserved for Autokey" , token , NTP_MAXKEY ) ;
 continue ;
 }
 token = nexttok ( & line ) ;
 if ( token == NULL ) {
 log_maybe ( & nerr , "authreadkeys: no key type for key %d" , keyno ) ;
 continue ;
 }

 if ( keytype == 0 ) {
 log_maybe ( & nerr , "authreadkeys: invalid type for key %d" , keyno ) ;
 continue ;
 }
 if ( EVP_get_digestbynid ( keytype ) == NULL ) {
 log_maybe ( & nerr , "authreadkeys: no algorithm for key %d" , keyno ) ;
 continue ;
 }

 log_maybe ( & nerr , "authreadkeys: invalid type for key %d" , keyno ) ;
 continue ;
 }
 keytype = KEY_TYPE_MD5 ;

 if ( token == NULL ) {
 log_maybe ( & nerr , "authreadkeys: no key for key %d" , keyno ) ;
 continue ;
 }
 len = strlen ( token ) ;
 if ( len <= 20 ) {
 MD5auth_setkey ( keyno , keytype , ( u_char * ) token , len ) ;
 }
 else {
 char hex [ ] = "0123456789abcdef" ;
 u_char temp ;
 char * ptr ;
 size_t jlim ;
 jlim = min ( len , 2 * sizeof ( keystr ) ) ;
 for ( j = 0 ;
 j < jlim ;
 j ++ ) {
 ptr = strchr ( hex , tolower ( ( unsigned char ) token [ j ] ) ) ;
 if ( ptr == NULL ) break ;
 temp = ( u_char ) ( ptr - hex ) ;
 if ( j & 1 ) keystr [ j / 2 ] |= temp ;
 else keystr [ j / 2 ] = temp << 4 ;
 }
 if ( j < jlim ) {
 log_maybe ( & nerr , "authreadkeys: invalid hex digit for key %d" , keyno ) ;
 continue ;
 }
 MD5auth_setkey ( keyno , keytype , keystr , jlim / 2 ) ;
 }
 }
 fclose ( fp ) ;
 if ( nerr > nerr_maxlimit ) {
 msyslog ( LOG_ERR , "authreadkeys: emergeny break after %u errors" , nerr ) ;
 return ( 0 ) ;
 }
 else if ( nerr > nerr_loglimit ) {
 msyslog ( LOG_ERR , "authreadkeys: found %u more error(s)" , nerr - nerr_loglimit ) ;
 }
 return ( 1 ) ;
 }