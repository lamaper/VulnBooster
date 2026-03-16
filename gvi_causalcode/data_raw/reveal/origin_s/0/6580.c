static err_status_t srtp_protect_aead ( srtp_ctx_t * ctx , srtp_stream_ctx_t * stream , void * rtp_hdr , unsigned int * pkt_octet_len ) {
 srtp_hdr_t * hdr = ( srtp_hdr_t * ) rtp_hdr ;
 uint32_t * enc_start ;
 unsigned int enc_octet_len = 0 ;
 xtd_seq_num_t est ;
 int delta ;
 err_status_t status ;
 int tag_len ;
 v128_t iv ;
 unsigned int aad_len ;
 debug_print ( mod_srtp , "function srtp_protect_aead" , NULL ) ;
 switch ( key_limit_update ( stream -> limit ) ) {
 case key_event_normal : break ;
 case key_event_hard_limit : srtp_handle_event ( ctx , stream , event_key_hard_limit ) ;
 return err_status_key_expired ;
 case key_event_soft_limit : default : srtp_handle_event ( ctx , stream , event_key_soft_limit ) ;
 break ;
 }
 tag_len = auth_get_tag_length ( stream -> rtp_auth ) ;
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtp_header + hdr -> cc ;
 if ( hdr -> x == 1 ) {
 srtp_hdr_xtnd_t * xtn_hdr = ( srtp_hdr_xtnd_t * ) enc_start ;
 enc_start += ( ntohs ( xtn_hdr -> length ) + 1 ) ;
 }
 if ( ! ( ( uint8_t * ) enc_start < ( uint8_t * ) hdr + * pkt_octet_len ) ) return err_status_parse_err ;
 enc_octet_len = ( unsigned int ) ( * pkt_octet_len - ( ( uint8_t * ) enc_start - ( uint8_t * ) hdr ) ) ;
 delta = rdbx_estimate_index ( & stream -> rtp_rdbx , & est , ntohs ( hdr -> seq ) ) ;
 status = rdbx_check ( & stream -> rtp_rdbx , delta ) ;
 if ( status ) {
 if ( status != err_status_replay_fail || ! stream -> allow_repeat_tx ) {
 return status ;
 }
 }
 else {
 rdbx_add_index ( & stream -> rtp_rdbx , delta ) ;
 }



 status = cipher_set_iv ( stream -> rtp_cipher , & iv , direction_encrypt ) ;
 if ( status ) {
 return err_status_cipher_fail ;
 }



 status = cipher_set_aad ( stream -> rtp_cipher , ( uint8_t * ) hdr , aad_len ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 status = cipher_encrypt ( stream -> rtp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) {
 return err_status_cipher_fail ;
 }
 status = cipher_get_tag ( stream -> rtp_cipher , ( uint8_t * ) enc_start + enc_octet_len , & tag_len ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 enc_octet_len += tag_len ;
 * pkt_octet_len += tag_len ;
 return err_status_ok ;
 }