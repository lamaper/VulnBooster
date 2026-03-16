err_status_t srtp_add_stream ( srtp_t session , const srtp_policy_t * policy ) {
 err_status_t status ;
 srtp_stream_t tmp ;
 if ( ( session == NULL ) || ( policy == NULL ) || ( policy -> key == NULL ) ) return err_status_bad_param ;
 status = srtp_stream_alloc ( & tmp , policy ) ;
 if ( status ) {
 return status ;
 }
 status = srtp_stream_init ( tmp , policy ) ;
 if ( status ) {
 crypto_free ( tmp ) ;
 return status ;
 }
 switch ( policy -> ssrc . type ) {
 case ( ssrc_any_outbound ) : if ( session -> stream_template ) {
 return err_status_bad_param ;
 }
 session -> stream_template = tmp ;
 session -> stream_template -> direction = dir_srtp_sender ;
 break ;
 case ( ssrc_any_inbound ) : if ( session -> stream_template ) {
 return err_status_bad_param ;
 }
 session -> stream_template = tmp ;
 session -> stream_template -> direction = dir_srtp_receiver ;
 break ;
 case ( ssrc_specific ) : tmp -> next = session -> stream_list ;
 session -> stream_list = tmp ;
 break ;
 case ( ssrc_undefined ) : default : crypto_free ( tmp ) ;
 return err_status_bad_param ;
 }
 return err_status_ok ;
 }