gpg_error_t _ksba_oid_from_buf ( const void * buffer , size_t buflen , unsigned char * * rbuf , size_t * rlength ) {
 gpg_error_t err ;
 char * string ;
 string = xtrymalloc ( buflen + 1 ) ;
 if ( ! string ) {
 * rbuf = NULL ;
 * rlength = 0 ;
 return gpg_error_from_syserror ( ) ;
 }
 memcpy ( string , buffer , buflen ) ;
 string [ buflen ] = 0 ;
 err = ksba_oid_from_str ( string , rbuf , rlength ) ;
 xfree ( string ) ;
 return err ;
 }