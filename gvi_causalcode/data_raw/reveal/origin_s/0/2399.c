void ssl3_free ( SSL * s ) {
 if ( s == NULL ) return ;

 if ( s -> s3 -> server_opaque_prf_input != NULL ) OPENSSL_free ( s -> s3 -> server_opaque_prf_input ) ;

 if ( s -> s3 -> rbuf . buf != NULL ) ssl3_release_read_buffer ( s ) ;
 if ( s -> s3 -> wbuf . buf != NULL ) ssl3_release_write_buffer ( s ) ;
 if ( s -> s3 -> rrec . comp != NULL ) OPENSSL_free ( s -> s3 -> rrec . comp ) ;



 if ( s -> s3 -> handshake_buffer ) {
 BIO_free ( s -> s3 -> handshake_buffer ) ;
 }
 if ( s -> s3 -> handshake_dgst ) ssl3_free_digest_list ( s ) ;


 OPENSSL_free ( s -> s3 ) ;
 s -> s3 = NULL ;
 }