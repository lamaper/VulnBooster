err_status_t srtp_stream_dealloc ( srtp_t session , srtp_stream_ctx_t * stream ) {
 err_status_t status ;
 if ( session -> stream_template && stream -> rtp_cipher == session -> stream_template -> rtp_cipher ) {
 }
 else {
 status = cipher_dealloc ( stream -> rtp_cipher ) ;
 if ( status ) return status ;
 }
 if ( session -> stream_template && stream -> rtp_auth == session -> stream_template -> rtp_auth ) {
 }
 else {
 status = auth_dealloc ( stream -> rtp_auth ) ;
 if ( status ) return status ;
 }
 if ( session -> stream_template && stream -> limit == session -> stream_template -> limit ) {
 }
 else {
 crypto_free ( stream -> limit ) ;
 }
 if ( session -> stream_template && stream -> rtcp_cipher == session -> stream_template -> rtcp_cipher ) {
 }
 else {
 status = cipher_dealloc ( stream -> rtcp_cipher ) ;
 if ( status ) return status ;
 }
 if ( session -> stream_template && stream -> rtcp_auth == session -> stream_template -> rtcp_auth ) {
 }
 else {
 status = auth_dealloc ( stream -> rtcp_auth ) ;
 if ( status ) return status ;
 }
 status = rdbx_dealloc ( & stream -> rtp_rdbx ) ;
 if ( status ) return status ;
 memset ( stream -> salt , 0 , SRTP_AEAD_SALT_LEN ) ;
 memset ( stream -> c_salt , 0 , SRTP_AEAD_SALT_LEN ) ;
 crypto_free ( stream ) ;
 return err_status_ok ;
 }