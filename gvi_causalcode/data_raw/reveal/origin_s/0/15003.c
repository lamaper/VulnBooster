err_status_t srtp_protect_rtcp ( srtp_t ctx , void * rtcp_hdr , int * pkt_octet_len ) {
 srtcp_hdr_t * hdr = ( srtcp_hdr_t * ) rtcp_hdr ;
 uint32_t * enc_start ;
 uint32_t * auth_start ;
 uint32_t * trailer ;
 unsigned int enc_octet_len = 0 ;
 uint8_t * auth_tag = NULL ;
 err_status_t status ;
 int tag_len ;
 srtp_stream_ctx_t * stream ;
 int prefix_len ;
 uint32_t seq_num ;
 if ( * pkt_octet_len < octets_in_rtcp_header ) return err_status_bad_param ;
 stream = srtp_get_stream ( ctx , hdr -> ssrc ) ;
 if ( stream == NULL ) {
 if ( ctx -> stream_template != NULL ) {
 srtp_stream_ctx_t * new_stream ;
 status = srtp_stream_clone ( ctx -> stream_template , hdr -> ssrc , & new_stream ) ;
 if ( status ) return status ;
 new_stream -> next = ctx -> stream_list ;
 ctx -> stream_list = new_stream ;
 stream = new_stream ;
 }
 else {
 return err_status_no_ctx ;
 }
 }
 if ( stream -> direction != dir_srtp_sender ) {
 if ( stream -> direction == dir_unknown ) {
 stream -> direction = dir_srtp_sender ;
 }
 else {
 srtp_handle_event ( ctx , stream , event_ssrc_collision ) ;
 }
 }
 if ( stream -> rtp_cipher -> algorithm == AES_128_GCM || stream -> rtp_cipher -> algorithm == AES_256_GCM ) {
 return srtp_protect_rtcp_aead ( ctx , stream , rtcp_hdr , ( unsigned int * ) pkt_octet_len ) ;
 }
 tag_len = auth_get_tag_length ( stream -> rtcp_auth ) ;
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtcp_header ;
 enc_octet_len = * pkt_octet_len - octets_in_rtcp_header ;
 trailer = ( uint32_t * ) ( ( char * ) enc_start + enc_octet_len ) ;
 if ( stream -> rtcp_services & sec_serv_conf ) {
 * trailer = htonl ( SRTCP_E_BIT ) ;
 }
 else {
 enc_start = NULL ;
 enc_octet_len = 0 ;
 * trailer = 0x00000000 ;
 }
 auth_start = ( uint32_t * ) hdr ;
 auth_tag = ( uint8_t * ) hdr + * pkt_octet_len + sizeof ( srtcp_trailer_t ) ;
 ekt_write_data ( stream -> ekt , auth_tag , tag_len , pkt_octet_len , rdbx_get_packet_index ( & stream -> rtp_rdbx ) ) ;
 status = rdb_increment ( & stream -> rtcp_rdb ) ;
 if ( status ) return status ;
 seq_num = rdb_get_value ( & stream -> rtcp_rdb ) ;
 * trailer |= htonl ( seq_num ) ;
 debug_print ( mod_srtp , "srtcp index: %x" , seq_num ) ;
 if ( stream -> rtcp_cipher -> type -> id == AES_ICM ) {
 v128_t iv ;
 iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = hdr -> ssrc ;
 iv . v32 [ 2 ] = htonl ( seq_num >> 16 ) ;
 iv . v32 [ 3 ] = htonl ( seq_num << 16 ) ;
 status = cipher_set_iv ( stream -> rtcp_cipher , & iv , direction_encrypt ) ;
 }
 else {
 v128_t iv ;
 iv . v32 [ 0 ] = 0 ;
 iv . v32 [ 1 ] = 0 ;
 iv . v32 [ 2 ] = 0 ;
 iv . v32 [ 3 ] = htonl ( seq_num ) ;
 status = cipher_set_iv ( stream -> rtcp_cipher , & iv , direction_encrypt ) ;
 }
 if ( status ) return err_status_cipher_fail ;
 if ( auth_start ) {
 prefix_len = auth_get_prefix_length ( stream -> rtcp_auth ) ;
 status = cipher_output ( stream -> rtcp_cipher , auth_tag , prefix_len ) ;
 debug_print ( mod_srtp , "keystream prefix: %s" , octet_string_hex_string ( auth_tag , prefix_len ) ) ;
 if ( status ) return err_status_cipher_fail ;
 }
 if ( enc_start ) {
 status = cipher_encrypt ( stream -> rtcp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) return err_status_cipher_fail ;
 }
 auth_start ( stream -> rtcp_auth ) ;
 status = auth_compute ( stream -> rtcp_auth , ( uint8_t * ) auth_start , ( * pkt_octet_len ) + sizeof ( srtcp_trailer_t ) , auth_tag ) ;
 debug_print ( mod_srtp , "srtcp auth tag: %s" , octet_string_hex_string ( auth_tag , tag_len ) ) ;
 if ( status ) return err_status_auth_fail ;
 * pkt_octet_len += ( tag_len + sizeof ( srtcp_trailer_t ) ) ;
 return err_status_ok ;
 }