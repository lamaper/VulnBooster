enum nss_status CONCAT ( _nss_files_end , ENTNAME ) ( void ) {
 __libc_lock_lock ( lock ) ;
 internal_endent ( ) ;
 keep_stream = 0 ;
 __libc_lock_unlock ( lock ) ;
 return NSS_STATUS_SUCCESS ;
 }