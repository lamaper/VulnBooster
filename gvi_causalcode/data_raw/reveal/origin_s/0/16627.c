err_status_t srtp_unprotect_rtcp ( srtp_t ctx , void * srtcp_hdr , int * pkt_octet_len ) {
 srtcp_hdr_t * hdr = ( srtcp_hdr_t * ) srtcp_hdr ;
 uint32_t * enc_start ;
 uint32_t * auth_start ;
 uint32_t * trailer ;
 unsigned int enc_octet_len = 0 ;
 uint8_t * auth_tag = NULL ;
 uint8_t tmp_tag [ SRTP_MAX_TAG_LEN ] ;
 uint8_t tag_copy [ SRTP_MAX_TAG_LEN ] ;
 err_status_t status ;
 unsigned int auth_len ;
 int tag_len ;
 srtp_stream_ctx_t * stream ;
 int prefix_len ;
 uint32_t seq_num ;
 int e_bit_in_packet ;
 int sec_serv_confidentiality ;
 if ( * pkt_octet_len < octets_in_rtcp_header + sizeof ( srtcp_trailer_t ) ) return err_status_bad_param ;
 stream = srtp_get_stream ( ctx , hdr -> ssrc ) ;
 if ( stream == NULL ) {
 if ( ctx -> stream_template != NULL ) {
 stream = ctx -> stream_template ;
 if ( stream -> ekt != NULL ) {
 status = srtp_stream_init_from_ekt ( stream , srtcp_hdr , * pkt_octet_len ) ;
 if ( status ) return status ;
 }
 debug_print ( mod_srtp , "srtcp using provisional stream (SSRC: 0x%08x)" , hdr -> ssrc ) ;
 }
 else {
 return err_status_no_ctx ;
 }
 }
 tag_len = auth_get_tag_length ( stream -> rtcp_auth ) ;
 if ( * pkt_octet_len < ( int ) ( octets_in_rtcp_header + tag_len + sizeof ( srtcp_trailer_t ) ) ) {
 return err_status_bad_param ;
 }
 if ( stream -> rtp_cipher -> algorithm == AES_128_GCM || stream -> rtp_cipher -> algorithm == AES_256_GCM ) {
 return srtp_unprotect_rtcp_aead ( ctx , stream , srtcp_hdr , ( unsigned int * ) pkt_octet_len ) ;
 }
 sec_serv_confidentiality = stream -> rtcp_services == sec_serv_conf || stream -> rtcp_services == sec_serv_conf_and_auth ;
 enc_octet_len = * pkt_octet_len - ( octets_in_rtcp_header + tag_len + sizeof ( srtcp_trailer_t ) ) ;
 trailer = ( uint32_t * ) ( ( char * ) hdr + * pkt_octet_len - ( tag_len + sizeof ( srtcp_trailer_t ) ) ) ;
 e_bit_in_packet = ( * ( ( unsigned char * ) trailer ) & SRTCP_E_BYTE_BIT ) == SRTCP_E_BYTE_BIT ;
 if ( e_bit_in_packet != sec_serv_confidentiality ) {
 return err_status_cant_check ;
 }
 if ( sec_serv_confidentiality ) {
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtcp_header ;
 }
 else {
 enc_octet_len = 0 ;
 enc_start = NULL ;
 }
 auth_start = ( uint32_t * ) hdr ;
 auth_len = * pkt_octet_len - tag_len ;
 auth_tag = ( uint8_t * ) hdr + auth_len ;
 if ( stream -> ekt ) {
 auth_tag -= ekt_octets_after_base_tag ( stream -> ekt ) ;
 memcpy ( tag_copy , auth_tag , tag_len ) ;
 octet_string_set_to_zero ( auth_tag , tag_len ) ;
 auth_tag = tag_copy ;
 auth_len += tag_len ;
 }
 seq_num = ntohl ( * trailer ) & SRTCP_INDEX_MASK ;
 debug_print ( mod_srtp , "srtcp index: %x" , seq_num ) ;
 status = rdb_check ( & stream -> rtcp_rdb , seq_num ) ;
 if ( status ) return status ;
 if ( stream -> rtcp_cipher -> type -> id == AES_ICM ) {
 v128_t iv ;
 iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = hdr -> ssrc ;
 iv . v32 [ 2 ] = htonl ( seq_num >> 16 ) ;
 iv . v32 [ 3 ] = htonl ( seq_num << 16 ) ;
 status = cipher_set_iv ( stream -> rtcp_cipher , & iv , direction_decrypt ) ;
 }
 else {
 v128_t iv ;
 iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = 0 ;
 iv . v32 [ 2 ] = 0 ;
 iv . v32 [ 3 ] = htonl ( seq_num ) ;
 status = cipher_set_iv ( stream -> rtcp_cipher , & iv , direction_decrypt ) ;
 }
 if ( status ) return err_status_cipher_fail ;
 auth_start ( stream -> rtcp_auth ) ;
 status = auth_compute ( stream -> rtcp_auth , ( uint8_t * ) auth_start , auth_len , tmp_tag ) ;
 debug_print ( mod_srtp , "srtcp computed tag: %s" , octet_string_hex_string ( tmp_tag , tag_len ) ) ;
 if ( status ) return err_status_auth_fail ;
 debug_print ( mod_srtp , "srtcp tag from packet: %s" , octet_string_hex_string ( auth_tag , tag_len ) ) ;
 if ( octet_string_is_eq ( tmp_tag , auth_tag , tag_len ) ) return err_status_auth_fail ;
 prefix_len = auth_get_prefix_length ( stream -> rtcp_auth ) ;
 if ( prefix_len ) {
 status = cipher_output ( stream -> rtcp_cipher , auth_tag , prefix_len ) ;
 debug_print ( mod_srtp , "keystream prefix: %s" , octet_string_hex_string ( auth_tag , prefix_len ) ) ;
 if ( status ) return err_status_cipher_fail ;
 }
 if ( enc_start ) {
 status = cipher_decrypt ( stream -> rtcp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) return err_status_cipher_fail ;
 }
 * pkt_octet_len -= ( tag_len + sizeof ( srtcp_trailer_t ) ) ;
 * pkt_octet_len -= ekt_octets_after_base_tag ( stream -> ekt ) ;
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
 rdb_add_index ( & stream -> rtcp_rdb , seq_num ) ;
 return err_status_ok ;
 }