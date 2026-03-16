err_status_t srtp_stream_init ( srtp_stream_ctx_t * srtp , const srtp_policy_t * p ) {
 err_status_t err ;
 debug_print ( mod_srtp , "initializing stream (SSRC: 0x%08x)" , p -> ssrc . value ) ;
 if ( p -> window_size != 0 && ( p -> window_size < 64 || p -> window_size >= 0x8000 ) ) return err_status_bad_param ;
 if ( p -> window_size != 0 ) err = rdbx_init ( & srtp -> rtp_rdbx , p -> window_size ) ;
 else err = rdbx_init ( & srtp -> rtp_rdbx , 128 ) ;
 if ( err ) return err ;

 uint64_t temp ;
 temp = make64 ( UINT_MAX , UINT_MAX ) ;
 key_limit_set ( srtp -> limit , temp ) ;
 }


 srtp -> rtp_services = p -> rtp . sec_serv ;
 srtp -> rtcp_services = p -> rtcp . sec_serv ;
 srtp -> direction = dir_unknown ;
 rdb_init ( & srtp -> rtcp_rdb ) ;
 if ( p -> allow_repeat_tx != 0 && p -> allow_repeat_tx != 1 ) {
 rdbx_dealloc ( & srtp -> rtp_rdbx ) ;
 return err_status_bad_param ;
 }
 srtp -> allow_repeat_tx = p -> allow_repeat_tx ;
 err = srtp_stream_init_keys ( srtp , p -> key ) ;
 if ( err ) {
 rdbx_dealloc ( & srtp -> rtp_rdbx ) ;
 return err ;
 }
 err = ekt_stream_init_from_policy ( srtp -> ekt , p -> ekt ) ;
 if ( err ) {
 rdbx_dealloc ( & srtp -> rtp_rdbx ) ;
 return err ;
 }
 return err_status_ok ;
 }