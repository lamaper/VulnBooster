void crypto_policy_set_aes_cm_128_hmac_sha1_32 ( crypto_policy_t * p ) {
 p -> cipher_type = AES_ICM ;
 p -> cipher_key_len = 30 ;
 p -> auth_type = HMAC_SHA1 ;
 p -> auth_key_len = 20 ;
 p -> auth_tag_len = 4 ;
 p -> sec_serv = sec_serv_conf_and_auth ;
 }