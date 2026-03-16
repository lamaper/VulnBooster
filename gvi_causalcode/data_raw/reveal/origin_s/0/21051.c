static enum nss_status internal_setent ( int stayopen ) {
 enum nss_status status = NSS_STATUS_SUCCESS ;
 if ( stream == NULL ) {
 stream = fopen ( DATAFILE , "rce" ) ;
 if ( stream == NULL ) status = errno == EAGAIN ? NSS_STATUS_TRYAGAIN : NSS_STATUS_UNAVAIL ;
 else {

 int result ;
 int flags ;
 result = flags = fcntl ( fileno ( stream ) , F_GETFD , 0 ) ;
 if ( result >= 0 ) {

 if ( __have_o_cloexec < 0 ) # endif {
 flags |= FD_CLOEXEC ;
 result = fcntl ( fileno ( stream ) , F_SETFD , flags ) ;
 }
 }
 if ( result < 0 ) {
 fclose ( stream ) ;
 stream = NULL ;
 status = NSS_STATUS_UNAVAIL ;
 }
 }

 }
 else rewind ( stream ) ;
 if ( stream != NULL ) keep_stream |= stayopen ;
 return status ;
 }