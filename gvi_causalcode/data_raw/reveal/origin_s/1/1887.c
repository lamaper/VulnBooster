enum nss_status CONCAT ( _nss_files_set , ENTNAME ) ( int stayopen ) {
 enum nss_status status ;
 __libc_lock_lock ( lock ) ;
 status = internal_setent ( stayopen ) ;
 if ( status == NSS_STATUS_SUCCESS && fgetpos ( stream , & position ) < 0 ) {
 fclose ( stream ) ;
 stream = NULL ;
 status = NSS_STATUS_UNAVAIL ;
 }
 last_use = getent ;
 __libc_lock_unlock ( lock ) ;
 return status ;
 }