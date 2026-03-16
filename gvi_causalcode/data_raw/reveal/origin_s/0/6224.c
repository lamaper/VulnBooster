enum nss_status CONCAT ( _nss_files_get , ENTNAME_r ) ( struct STRUCTURE * result , char * buffer , size_t buflen , int * errnop H_ERRNO_PROTO ) {
 enum nss_status status = NSS_STATUS_SUCCESS ;
 __libc_lock_lock ( lock ) ;
 if ( stream == NULL ) {
 int save_errno = errno ;
 status = internal_setent ( 0 ) ;
 __set_errno ( save_errno ) ;
 if ( status == NSS_STATUS_SUCCESS && fgetpos ( stream , & position ) < 0 ) {
 fclose ( stream ) ;
 stream = NULL ;
 status = NSS_STATUS_UNAVAIL ;
 }
 }
 if ( status == NSS_STATUS_SUCCESS ) {
 if ( last_use != getent ) {
 if ( fsetpos ( stream , & position ) < 0 ) status = NSS_STATUS_UNAVAIL ;
 else last_use = getent ;
 }
 if ( status == NSS_STATUS_SUCCESS ) {
 status = internal_getent ( result , buffer , buflen , errnop H_ERRNO_ARG EXTRA_ARGS_VALUE ) ;
 if ( status == NSS_STATUS_SUCCESS ) fgetpos ( stream , & position ) ;
 else last_use = nouse ;
 }
 }
 __libc_lock_unlock ( lock ) ;
 return status ;
 }