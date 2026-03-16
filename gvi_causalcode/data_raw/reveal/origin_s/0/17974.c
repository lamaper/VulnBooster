err_status_t srtp_unprotect ( srtp_ctx_t * ctx , void * srtp_hdr , int * pkt_octet_len ) {
 srtp_hdr_t * hdr = ( srtp_hdr_t * ) srtp_hdr ;
 uint32_t * enc_start ;
 uint32_t * auth_start ;
 unsigned int enc_octet_len = 0 ;
 uint8_t * auth_tag = NULL ;
 xtd_seq_num_t est ;
 int delta ;
 v128_t iv ;
 err_status_t status ;
 srtp_stream_ctx_t * stream ;
 uint8_t tmp_tag [ SRTP_MAX_TAG_LEN ] ;
 int tag_len , prefix_len ;
 debug_print ( mod_srtp , "function srtp_unprotect" , NULL ) ;
 status = srtp_validate_rtp_header ( srtp_hdr , pkt_octet_len ) ;
 if ( status ) return status ;
 if ( * pkt_octet_len < octets_in_rtp_header ) return err_status_bad_param ;
 stream = srtp_get_stream ( ctx , hdr -> ssrc ) ;
 if ( stream == NULL ) {
 if ( ctx -> stream_template != NULL ) {
 stream = ctx -> stream_template ;
 debug_print ( mod_srtp , "using provisional stream (SSRC: 0x%08x)" , hdr -> ssrc ) ;

 delta = low32 ( est ) ;

 delta = ( int ) est ;

 else {
 return err_status_no_ctx ;
 }
 }
 else {
 delta = rdbx_estimate_index ( & stream -> rtp_rdbx , & est , ntohs ( hdr -> seq ) ) ;
 status = rdbx_check ( & stream -> rtp_rdbx , delta ) ;
 if ( status ) return status ;
 }



 return srtp_unprotect_aead ( ctx , stream , delta , est , srtp_hdr , ( unsigned int * ) pkt_octet_len ) ;
 }
 tag_len = auth_get_tag_length ( stream -> rtp_auth ) ;
 if ( stream -> rtp_cipher -> type -> id == AES_ICM || stream -> rtp_cipher -> type -> id == AES_256_ICM ) {
 iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = hdr -> ssrc ;



 }
 else {

 iv . v32 [ 1 ] = 0 ;


 status = cipher_set_iv ( stream -> rtp_cipher , & iv , direction_decrypt ) ;
 }
 if ( status ) return err_status_cipher_fail ;



 enc_start = ( uint32_t * ) hdr + uint32s_in_rtp_header + hdr -> cc ;
 if ( hdr -> x == 1 ) {
 srtp_hdr_xtnd_t * xtn_hdr = ( srtp_hdr_xtnd_t * ) enc_start ;
 enc_start += ( ntohs ( xtn_hdr -> length ) + 1 ) ;
 }
 if ( ! ( ( uint8_t * ) enc_start < ( uint8_t * ) hdr + ( * pkt_octet_len - tag_len ) ) ) return err_status_parse_err ;
 enc_octet_len = ( uint32_t ) ( * pkt_octet_len - tag_len - ( ( uint8_t * ) enc_start - ( uint8_t * ) hdr ) ) ;
 }
 else {
 enc_start = NULL ;
 }
 if ( stream -> rtp_services & sec_serv_auth ) {
 auth_start = ( uint32_t * ) hdr ;
 auth_tag = ( uint8_t * ) hdr + * pkt_octet_len - tag_len ;
 }
 else {
 auth_start = NULL ;
 auth_tag = NULL ;
 }
 if ( auth_start ) {
 if ( stream -> rtp_auth -> prefix_len != 0 ) {
 prefix_len = auth_get_prefix_length ( stream -> rtp_auth ) ;
 status = cipher_output ( stream -> rtp_cipher , tmp_tag , prefix_len ) ;
 debug_print ( mod_srtp , "keystream prefix: %s" , octet_string_hex_string ( tmp_tag , prefix_len ) ) ;
 if ( status ) return err_status_cipher_fail ;
 }
 status = auth_start ( stream -> rtp_auth ) ;
 if ( status ) return status ;
 status = auth_update ( stream -> rtp_auth , ( uint8_t * ) auth_start , * pkt_octet_len - tag_len ) ;
 status = auth_compute ( stream -> rtp_auth , ( uint8_t * ) & est , 4 , tmp_tag ) ;
 debug_print ( mod_srtp , "computed auth tag: %s" , octet_string_hex_string ( tmp_tag , tag_len ) ) ;
 debug_print ( mod_srtp , "packet auth tag: %s" , octet_string_hex_string ( auth_tag , tag_len ) ) ;
 if ( status ) return err_status_auth_fail ;
 if ( octet_string_is_eq ( tmp_tag , auth_tag , tag_len ) ) return err_status_auth_fail ;
 }
 switch ( key_limit_update ( stream -> limit ) ) {
 case key_event_normal : break ;
 case key_event_soft_limit : srtp_handle_event ( ctx , stream , event_key_soft_limit ) ;
 break ;
 case key_event_hard_limit : srtp_handle_event ( ctx , stream , event_key_hard_limit ) ;
 return err_status_key_expired ;
 default : break ;
 }
 if ( enc_start ) {
 status = cipher_decrypt ( stream -> rtp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) return err_status_cipher_fail ;
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
 if ( status ) return status ;
 new_stream -> next = ctx -> stream_list ;
 ctx -> stream_list = new_stream ;
 stream = new_stream ;
 }
 rdbx_add_index ( & stream -> rtp_rdbx , delta ) ;
 * pkt_octet_len -= tag_len ;
 return err_status_ok ;
 }