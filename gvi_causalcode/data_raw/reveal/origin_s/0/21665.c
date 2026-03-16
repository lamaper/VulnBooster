static err_status_t srtp_unprotect_aead ( srtp_ctx_t * ctx , srtp_stream_ctx_t * stream , int delta , xtd_seq_num_t est , void * srtp_hdr , unsigned int * pkt_octet_len ) {
 srtp_hdr_t * hdr = ( srtp_hdr_t * ) srtp_hdr ;
 uint32_t * enc_start ;
 unsigned int enc_octet_len = 0 ;
 v128_t iv ;
 err_status_t status ;
 int tag_len ;
 unsigned int aad_len ;
 debug_print ( mod_srtp , "function srtp_unprotect_aead" , NULL ) ;



 srtp_calc_aead_iv ( stream , & iv , & est , hdr ) ;
 status = cipher_set_iv ( stream -> rtp_cipher , & iv , direction_decrypt ) ;
 if ( status ) {
 return err_status_cipher_fail ;
 }
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtp_header + hdr -> cc ;
 if ( hdr -> x == 1 ) {
 srtp_hdr_xtnd_t * xtn_hdr = ( srtp_hdr_xtnd_t * ) enc_start ;
 enc_start += ( ntohs ( xtn_hdr -> length ) + 1 ) ;
 }
 if ( ! ( ( uint8_t * ) enc_start < ( uint8_t * ) hdr + ( * pkt_octet_len - tag_len ) ) ) return err_status_parse_err ;
 enc_octet_len = ( unsigned int ) ( * pkt_octet_len - ( ( uint8_t * ) enc_start - ( uint8_t * ) hdr ) ) ;
 if ( enc_octet_len < ( unsigned int ) tag_len ) {
 return err_status_cipher_fail ;
 }
 switch ( key_limit_update ( stream -> limit ) ) {
 case key_event_normal : break ;
 case key_event_soft_limit : srtp_handle_event ( ctx , stream , event_key_soft_limit ) ;
 break ;
 case key_event_hard_limit : srtp_handle_event ( ctx , stream , event_key_hard_limit ) ;
 return err_status_key_expired ;
 default : break ;
 }
 aad_len = ( uint8_t * ) enc_start - ( uint8_t * ) hdr ;
 status = cipher_set_aad ( stream -> rtp_cipher , ( uint8_t * ) hdr , aad_len ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 status = cipher_decrypt ( stream -> rtp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) {
 return status ;
 }
 if ( stream -> direction != dir_srtp_receiver ) {
 if ( stream -> direction == dir_unknown ) {
 stream -> direction = dir_srtp_receiver ;
 }
 else {
 srtp_handle_event ( ctx , stream , event_ssrc_collision ) ;
 }
 }
 if ( stream == ctx -> stream_template ) {
 srtp_stream_ctx_t * new_stream ;
 status = srtp_stream_clone ( ctx -> stream_template , hdr -> ssrc , & new_stream ) ;
 if ( status ) {
 return status ;
 }
 new_stream -> next = ctx -> stream_list ;
 ctx -> stream_list = new_stream ;
 stream = new_stream ;
 }
 rdbx_add_index ( & stream -> rtp_rdbx , delta ) ;
 * pkt_octet_len -= tag_len ;
 return err_status_ok ;
 }