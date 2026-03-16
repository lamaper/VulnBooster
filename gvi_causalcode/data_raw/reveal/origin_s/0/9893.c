int ssl3_setup_read_buffer ( SSL * s ) {
 unsigned char * p ;
 size_t len , align = 0 , headerlen ;
 if ( SSL_version ( s ) == DTLS1_VERSION || SSL_version ( s ) == DTLS1_BAD_VER ) headerlen = DTLS1_RT_HEADER_LENGTH ;
 else headerlen = SSL3_RT_HEADER_LENGTH ;


 len = SSL3_RT_MAX_PLAIN_LENGTH + SSL3_RT_MAX_ENCRYPTED_OVERHEAD + headerlen + align ;
 if ( s -> options & SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER ) {
 s -> s3 -> init_extra = 1 ;
 len += SSL3_RT_MAX_EXTRA ;
 }


 s -> s3 -> rbuf . buf = p ;
 s -> s3 -> rbuf . len = len ;
 }
 s -> packet = & ( s -> s3 -> rbuf . buf [ 0 ] ) ;
 return 1 ;
 err : SSLerr ( SSL_F_SSL3_SETUP_READ_BUFFER , ERR_R_MALLOC_FAILURE ) ;
 return 0 ;
 }