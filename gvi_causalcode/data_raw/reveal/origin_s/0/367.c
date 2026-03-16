static err_status_t srtp_unprotect_rtcp_aead ( srtp_t ctx , srtp_stream_ctx_t * stream , void * srtcp_hdr , unsigned int * pkt_octet_len ) {
 srtcp_hdr_t * hdr = ( srtcp_hdr_t * ) srtcp_hdr ;
 uint32_t * enc_start ;
 uint32_t * trailer ;
 unsigned int enc_octet_len = 0 ;
 uint8_t * auth_tag = NULL ;
 err_status_t status ;
 int tag_len ;
 unsigned int tmp_len ;
 uint32_t seq_num ;
 v128_t iv ;
 uint32_t tseq ;
 tag_len = auth_get_tag_length ( stream -> rtcp_auth ) ;
 trailer = ( uint32_t * ) ( ( char * ) hdr + * pkt_octet_len - sizeof ( srtcp_trailer_t ) ) ;
 enc_octet_len = * pkt_octet_len - ( octets_in_rtcp_header + sizeof ( srtcp_trailer_t ) ) ;
 auth_tag = ( uint8_t * ) hdr + * pkt_octet_len - tag_len - sizeof ( srtcp_trailer_t ) ;
 if ( * ( ( unsigned char * ) trailer ) & SRTCP_E_BYTE_BIT ) {
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtcp_header ;
 }
 else {
 enc_octet_len = 0 ;
 enc_start = NULL ;
 }
 seq_num = ntohl ( * trailer ) & SRTCP_INDEX_MASK ;
 debug_print ( mod_srtp , "srtcp index: %x" , seq_num ) ;
 status = rdb_check ( & stream -> rtcp_rdb , seq_num ) ;
 if ( status ) {
 return status ;
 }
 srtp_calc_aead_iv_srtcp ( stream , & iv , seq_num , hdr ) ;
 status = cipher_set_iv ( stream -> rtcp_cipher , & iv , direction_decrypt ) ;
 if ( status ) {
 return err_status_cipher_fail ;
 }
 if ( enc_start ) {
 status = cipher_set_aad ( stream -> rtcp_cipher , ( uint8_t * ) hdr , octets_in_rtcp_header ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 }
 else {
 status = cipher_set_aad ( stream -> rtcp_cipher , ( uint8_t * ) hdr , ( * pkt_octet_len - tag_len - sizeof ( srtcp_trailer_t ) ) ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 }
 tseq = htonl ( * trailer ) ;
 status = cipher_set_aad ( stream -> rtcp_cipher , ( uint8_t * ) & tseq , sizeof ( srtcp_trailer_t ) ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 if ( enc_start ) {
 status = cipher_decrypt ( stream -> rtcp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) {
 return status ;
 }
 }
 else {
 tmp_len = tag_len ;
 status = cipher_decrypt ( stream -> rtcp_cipher , ( uint8_t * ) auth_tag , & tmp_len ) ;
 if ( status ) {
 return status ;
 }
 }
 * pkt_octet_len -= ( tag_len + sizeof ( srtcp_trailer_t ) ) ;
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
 rdb_add_index ( & stream -> rtcp_rdb , seq_num ) ;
 return err_status_ok ;
 }