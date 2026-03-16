int ssl3_setup_write_buffer ( SSL * s ) {
 unsigned char * p ;
 size_t len , align = 0 , headerlen ;
 if ( SSL_version ( s ) == DTLS1_VERSION || SSL_version ( s ) == DTLS1_BAD_VER ) headerlen = DTLS1_RT_HEADER_LENGTH + 1 ;
 else headerlen = SSL3_RT_HEADER_LENGTH ;


 len = s -> max_send_fragment + SSL3_RT_SEND_MAX_ENCRYPTED_OVERHEAD + headerlen + align ;


 if ( ( p = freelist_extract ( s -> ctx , 0 , len ) ) == NULL ) goto err ;
 s -> s3 -> wbuf . buf = p ;
 s -> s3 -> wbuf . len = len ;
 }
 return 1 ;
 err : SSLerr ( SSL_F_SSL3_SETUP_WRITE_BUFFER , ERR_R_MALLOC_FAILURE ) ;
 return 0 ;
 }