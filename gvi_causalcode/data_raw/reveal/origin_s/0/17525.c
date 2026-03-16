int dtls1_read_failed ( SSL * s , int code ) {
 if ( code > 0 ) {
 SSLerr ( SSL_F_DTLS1_READ_FAILED , ERR_R_INTERNAL_ERROR ) ;
 return 1 ;
 }
 if ( ! dtls1_is_timer_expired ( s ) ) {
 return code ;
 }

 BIO_set_flags ( SSL_get_rbio ( s ) , BIO_FLAGS_READ ) ;
 return code ;
 }
 return dtls1_handle_timeout ( s ) ;
 }