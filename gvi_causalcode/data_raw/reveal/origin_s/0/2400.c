enum nss_status _nss_nis_setaliasent ( void ) {
 __libc_lock_lock ( lock ) ;
 new_start = 1 ;
 if ( oldkey != NULL ) {
 free ( oldkey ) ;
 oldkey = NULL ;
 oldkeylen = 0 ;
 }
 __libc_lock_unlock ( lock ) ;
 return NSS_STATUS_SUCCESS ;
 }