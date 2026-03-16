static err_status_t srtp_protect_rtcp_aead ( srtp_t ctx , srtp_stream_ctx_t * stream , void * rtcp_hdr , unsigned int * pkt_octet_len ) {
 srtcp_hdr_t * hdr = ( srtcp_hdr_t * ) rtcp_hdr ;
 uint32_t * enc_start ;
 uint32_t * trailer ;
 unsigned int enc_octet_len = 0 ;
 uint8_t * auth_tag = NULL ;
 err_status_t status ;
 int tag_len ;
 uint32_t seq_num ;
 v128_t iv ;
 uint32_t tseq ;
 tag_len = auth_get_tag_length ( stream -> rtcp_auth ) ;
 enc_start = ( uint32_t * ) hdr + uint32s_in_rtcp_header ;
 enc_octet_len = * pkt_octet_len - octets_in_rtcp_header ;
 trailer = ( uint32_t * ) ( ( char * ) enc_start + enc_octet_len + tag_len ) ;
 if ( stream -> rtcp_services & sec_serv_conf ) {
 * trailer = htonl ( SRTCP_E_BIT ) ;
 }
 else {
 enc_start = NULL ;
 enc_octet_len = 0 ;
 * trailer = 0x00000000 ;
 }
 auth_tag = ( uint8_t * ) hdr + * pkt_octet_len ;
 status = rdb_increment ( & stream -> rtcp_rdb ) ;
 if ( status ) {
 return status ;
 }
 seq_num = rdb_get_value ( & stream -> rtcp_rdb ) ;
 * trailer |= htonl ( seq_num ) ;
 debug_print ( mod_srtp , "srtcp index: %x" , seq_num ) ;
 srtp_calc_aead_iv_srtcp ( stream , & iv , seq_num , hdr ) ;
 status = cipher_set_iv ( stream -> rtcp_cipher , & iv , direction_encrypt ) ;
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
 status = cipher_set_aad ( stream -> rtcp_cipher , ( uint8_t * ) hdr , * pkt_octet_len ) ;
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
 status = cipher_encrypt ( stream -> rtcp_cipher , ( uint8_t * ) enc_start , & enc_octet_len ) ;
 if ( status ) {
 return err_status_cipher_fail ;
 }
 status = cipher_get_tag ( stream -> rtcp_cipher , ( uint8_t * ) auth_tag , & tag_len ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 enc_octet_len += tag_len ;
 }
 else {
 unsigned int nolen = 0 ;
 status = cipher_encrypt ( stream -> rtcp_cipher , NULL , & nolen ) ;
 if ( status ) {
 return err_status_cipher_fail ;
 }
 status = cipher_get_tag ( stream -> rtcp_cipher , ( uint8_t * ) auth_tag , & tag_len ) ;
 if ( status ) {
 return ( err_status_cipher_fail ) ;
 }
 enc_octet_len += tag_len ;
 }
 * pkt_octet_len += ( tag_len + sizeof ( srtcp_trailer_t ) ) ;
 return err_status_ok ;
 }