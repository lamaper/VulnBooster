err_status_t srtp_dealloc ( srtp_t session ) {
 srtp_stream_ctx_t * stream ;
 err_status_t status ;
 stream = session -> stream_list ;
 while ( stream != NULL ) {
 srtp_stream_t next = stream -> next ;
 status = srtp_stream_dealloc ( session , stream ) ;
 if ( status ) return status ;
 stream = next ;
 }
 if ( session -> stream_template != NULL ) {
 status = auth_dealloc ( session -> stream_template -> rtcp_auth ) ;
 if ( status ) return status ;
 status = cipher_dealloc ( session -> stream_template -> rtcp_cipher ) ;
 if ( status ) return status ;
 crypto_free ( session -> stream_template -> limit ) ;
 status = cipher_dealloc ( session -> stream_template -> rtp_cipher ) ;
 if ( status ) return status ;
 status = auth_dealloc ( session -> stream_template -> rtp_auth ) ;
 if ( status ) return status ;
 status = rdbx_dealloc ( & session -> stream_template -> rtp_rdbx ) ;
 if ( status ) return status ;
 crypto_free ( session -> stream_template ) ;
 }
 crypto_free ( session ) ;
 return err_status_ok ;
 }