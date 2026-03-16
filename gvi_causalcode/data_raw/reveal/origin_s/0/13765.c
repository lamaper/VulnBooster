gpg_error_t ksba_oid_from_str ( const char * string , unsigned char * * rbuf , size_t * rlength ) {
 unsigned char * buf ;
 size_t buflen ;
 unsigned long val1 , val ;
 const char * endp ;
 int arcno ;
 if ( ! string || ! rbuf || ! rlength ) return gpg_error ( GPG_ERR_INV_VALUE ) ;
 * rbuf = NULL ;
 * rlength = 0 ;
 if ( ! strncmp ( string , "oid." , 4 ) || ! strncmp ( string , "OID." , 4 ) ) string += 4 ;
 if ( ! * string ) return gpg_error ( GPG_ERR_INV_VALUE ) ;
 buf = xtrymalloc ( strlen ( string ) + 2 ) ;
 if ( ! buf ) return gpg_error ( GPG_ERR_ENOMEM ) ;
 buflen = 0 ;
 val1 = 0 ;
 arcno = 0 ;
 do {
 arcno ++ ;
 val = strtoul ( string , ( char * * ) & endp , 10 ) ;
 if ( ! digitp ( string ) || ! ( * endp == '.' || ! * endp ) ) {
 xfree ( buf ) ;
 return gpg_error ( GPG_ERR_INV_OID_STRING ) ;
 }
 if ( * endp == '.' ) string = endp + 1 ;
 if ( arcno == 1 ) {
 if ( val > 2 ) break ;
 val1 = val ;
 }
 else if ( arcno == 2 ) {
 if ( val1 < 2 ) {
 if ( val > 39 ) {
 xfree ( buf ) ;
 return gpg_error ( GPG_ERR_INV_OID_STRING ) ;
 }
 buf [ buflen ++ ] = val1 * 40 + val ;
 }
 else {
 val += 80 ;
 buflen = make_flagged_int ( val , buf , buflen ) ;
 }
 }
 else {
 buflen = make_flagged_int ( val , buf , buflen ) ;
 }
 }
 while ( * endp == '.' ) ;
 if ( arcno == 1 ) {
 xfree ( buf ) ;
 return gpg_error ( GPG_ERR_INV_OID_STRING ) ;
 }
 * rbuf = buf ;
 * rlength = buflen ;
 return 0 ;
 }