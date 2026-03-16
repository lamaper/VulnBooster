err_status_t srtp_stream_alloc ( srtp_stream_ctx_t * * str_ptr , const srtp_policy_t * p ) {
 srtp_stream_ctx_t * str ;
 err_status_t stat ;
 str = ( srtp_stream_ctx_t * ) crypto_alloc ( sizeof ( srtp_stream_ctx_t ) ) ;
 if ( str == NULL ) return err_status_alloc_fail ;
 * str_ptr = str ;
 stat = crypto_kernel_alloc_cipher ( p -> rtp . cipher_type , & str -> rtp_cipher , p -> rtp . cipher_key_len , p -> rtp . auth_tag_len ) ;
 if ( stat ) {
 crypto_free ( str ) ;
 return stat ;
 }
 stat = crypto_kernel_alloc_auth ( p -> rtp . auth_type , & str -> rtp_auth , p -> rtp . auth_key_len , p -> rtp . auth_tag_len ) ;
 if ( stat ) {
 cipher_dealloc ( str -> rtp_cipher ) ;
 crypto_free ( str ) ;
 return stat ;
 }
 str -> limit = ( key_limit_ctx_t * ) crypto_alloc ( sizeof ( key_limit_ctx_t ) ) ;
 if ( str -> limit == NULL ) {
 auth_dealloc ( str -> rtp_auth ) ;
 cipher_dealloc ( str -> rtp_cipher ) ;
 crypto_free ( str ) ;
 return err_status_alloc_fail ;
 }
 stat = crypto_kernel_alloc_cipher ( p -> rtcp . cipher_type , & str -> rtcp_cipher , p -> rtcp . cipher_key_len , p -> rtcp . auth_tag_len ) ;
 if ( stat ) {
 auth_dealloc ( str -> rtp_auth ) ;
 cipher_dealloc ( str -> rtp_cipher ) ;
 crypto_free ( str -> limit ) ;
 crypto_free ( str ) ;
 return stat ;
 }
 stat = crypto_kernel_alloc_auth ( p -> rtcp . auth_type , & str -> rtcp_auth , p -> rtcp . auth_key_len , p -> rtcp . auth_tag_len ) ;
 if ( stat ) {
 cipher_dealloc ( str -> rtcp_cipher ) ;
 auth_dealloc ( str -> rtp_auth ) ;
 cipher_dealloc ( str -> rtp_cipher ) ;
 crypto_free ( str -> limit ) ;
 crypto_free ( str ) ;
 return stat ;
 }
 stat = ekt_alloc ( & str -> ekt , p -> ekt ) ;
 if ( stat ) {
 auth_dealloc ( str -> rtcp_auth ) ;
 cipher_dealloc ( str -> rtcp_cipher ) ;
 auth_dealloc ( str -> rtp_auth ) ;
 cipher_dealloc ( str -> rtp_cipher ) ;
 crypto_free ( str -> limit ) ;
 crypto_free ( str ) ;
 return stat ;
 }
 return err_status_ok ;
 }