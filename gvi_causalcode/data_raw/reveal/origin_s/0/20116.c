err_status_t srtp_stream_clone ( const srtp_stream_ctx_t * stream_template , uint32_t ssrc , srtp_stream_ctx_t * * str_ptr ) {
 err_status_t status ;
 srtp_stream_ctx_t * str ;
 debug_print ( mod_srtp , "cloning stream (SSRC: 0x%08x)" , ssrc ) ;
 str = ( srtp_stream_ctx_t * ) crypto_alloc ( sizeof ( srtp_stream_ctx_t ) ) ;
 if ( str == NULL ) return err_status_alloc_fail ;
 * str_ptr = str ;
 str -> rtp_cipher = stream_template -> rtp_cipher ;
 str -> rtp_auth = stream_template -> rtp_auth ;
 str -> rtcp_cipher = stream_template -> rtcp_cipher ;
 str -> rtcp_auth = stream_template -> rtcp_auth ;
 status = key_limit_clone ( stream_template -> limit , & str -> limit ) ;
 if ( status ) {
 crypto_free ( * str_ptr ) ;
 * str_ptr = NULL ;
 return status ;
 }
 status = rdbx_init ( & str -> rtp_rdbx , rdbx_get_window_size ( & stream_template -> rtp_rdbx ) ) ;
 if ( status ) {
 crypto_free ( * str_ptr ) ;
 * str_ptr = NULL ;
 return status ;
 }
 rdb_init ( & str -> rtcp_rdb ) ;
 str -> allow_repeat_tx = stream_template -> allow_repeat_tx ;
 str -> ssrc = ssrc ;
 str -> direction = stream_template -> direction ;
 str -> rtp_services = stream_template -> rtp_services ;
 str -> rtcp_services = stream_template -> rtcp_services ;
 str -> ekt = stream_template -> ekt ;
 memcpy ( str -> salt , stream_template -> salt , SRTP_AEAD_SALT_LEN ) ;
 memcpy ( str -> c_salt , stream_template -> c_salt , SRTP_AEAD_SALT_LEN ) ;
 str -> next = NULL ;
 return err_status_ok ;
 }