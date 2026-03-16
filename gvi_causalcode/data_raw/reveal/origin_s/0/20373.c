err_status_t srtp_stream_init_keys ( srtp_stream_ctx_t * srtp , const void * key ) {
 err_status_t stat ;
 srtp_kdf_t kdf ;
 uint8_t tmp_key [ MAX_SRTP_KEY_LEN ] ;
 int kdf_keylen = 30 , rtp_keylen , rtcp_keylen ;
 int rtp_base_key_len , rtp_salt_len ;
 int rtcp_base_key_len , rtcp_salt_len ;
 rtp_keylen = cipher_get_key_length ( srtp -> rtp_cipher ) ;
 rtcp_keylen = cipher_get_key_length ( srtp -> rtcp_cipher ) ;
 rtp_base_key_len = base_key_length ( srtp -> rtp_cipher -> type , rtp_keylen ) ;
 rtp_salt_len = rtp_keylen - rtp_base_key_len ;
 if ( rtp_keylen > kdf_keylen ) {
 kdf_keylen = 46 ;
 }
 if ( rtcp_keylen > kdf_keylen ) {
 kdf_keylen = 46 ;
 }
 debug_print ( mod_srtp , "srtp key len: %d" , rtp_keylen ) ;
 debug_print ( mod_srtp , "srtcp key len: %d" , rtcp_keylen ) ;
 debug_print ( mod_srtp , "base key len: %d" , rtp_base_key_len ) ;
 debug_print ( mod_srtp , "kdf key len: %d" , kdf_keylen ) ;
 debug_print ( mod_srtp , "rtp salt len: %d" , rtp_salt_len ) ;
 memset ( tmp_key , 0x0 , MAX_SRTP_KEY_LEN ) ;
 memcpy ( tmp_key , key , ( rtp_base_key_len + rtp_salt_len ) ) ;
 stat = srtp_kdf_init ( & kdf , AES_ICM , ( const uint8_t * ) tmp_key , kdf_keylen ) ;
 if ( stat ) {
 return err_status_init_fail ;
 }
 stat = srtp_kdf_generate ( & kdf , label_rtp_encryption , tmp_key , rtp_base_key_len ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 debug_print ( mod_srtp , "cipher key: %s" , octet_string_hex_string ( tmp_key , rtp_base_key_len ) ) ;
 if ( rtp_salt_len > 0 ) {
 debug_print ( mod_srtp , "found rtp_salt_len > 0, generating salt" , NULL ) ;
 stat = srtp_kdf_generate ( & kdf , label_rtp_salt , tmp_key + rtp_base_key_len , rtp_salt_len ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 memcpy ( srtp -> salt , tmp_key + rtp_base_key_len , SRTP_AEAD_SALT_LEN ) ;
 }
 if ( rtp_salt_len > 0 ) {
 debug_print ( mod_srtp , "cipher salt: %s" , octet_string_hex_string ( tmp_key + rtp_base_key_len , rtp_salt_len ) ) ;
 }
 stat = cipher_init ( srtp -> rtp_cipher , tmp_key ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 stat = srtp_kdf_generate ( & kdf , label_rtp_msg_auth , tmp_key , auth_get_key_length ( srtp -> rtp_auth ) ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 debug_print ( mod_srtp , "auth key: %s" , octet_string_hex_string ( tmp_key , auth_get_key_length ( srtp -> rtp_auth ) ) ) ;
 stat = auth_init ( srtp -> rtp_auth , tmp_key ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 rtcp_base_key_len = base_key_length ( srtp -> rtcp_cipher -> type , rtcp_keylen ) ;
 rtcp_salt_len = rtcp_keylen - rtcp_base_key_len ;
 debug_print ( mod_srtp , "rtcp salt len: %d" , rtcp_salt_len ) ;
 stat = srtp_kdf_generate ( & kdf , label_rtcp_encryption , tmp_key , rtcp_base_key_len ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 if ( rtcp_salt_len > 0 ) {
 debug_print ( mod_srtp , "found rtcp_salt_len > 0, generating rtcp salt" , NULL ) ;
 stat = srtp_kdf_generate ( & kdf , label_rtcp_salt , tmp_key + rtcp_base_key_len , rtcp_salt_len ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 memcpy ( srtp -> c_salt , tmp_key + rtcp_base_key_len , SRTP_AEAD_SALT_LEN ) ;
 }
 debug_print ( mod_srtp , "rtcp cipher key: %s" , octet_string_hex_string ( tmp_key , rtcp_base_key_len ) ) ;
 if ( rtcp_salt_len > 0 ) {
 debug_print ( mod_srtp , "rtcp cipher salt: %s" , octet_string_hex_string ( tmp_key + rtcp_base_key_len , rtcp_salt_len ) ) ;
 }
 stat = cipher_init ( srtp -> rtcp_cipher , tmp_key ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 stat = srtp_kdf_generate ( & kdf , label_rtcp_msg_auth , tmp_key , auth_get_key_length ( srtp -> rtcp_auth ) ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 debug_print ( mod_srtp , "rtcp auth key: %s" , octet_string_hex_string ( tmp_key , auth_get_key_length ( srtp -> rtcp_auth ) ) ) ;
 stat = auth_init ( srtp -> rtcp_auth , tmp_key ) ;
 if ( stat ) {
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 return err_status_init_fail ;
 }
 stat = srtp_kdf_clear ( & kdf ) ;
 octet_string_set_to_zero ( tmp_key , MAX_SRTP_KEY_LEN ) ;
 if ( stat ) return err_status_init_fail ;
 return err_status_ok ;
 }