void crypto_policy_set_null_cipher_hmac_sha1_80 ( crypto_policy_t * p ) {
 p -> cipher_type = NULL_CIPHER ;
 p -> cipher_key_len = 0 ;
 p -> auth_type = HMAC_SHA1 ;
 p -> auth_key_len = 20 ;
 p -> auth_tag_len = 10 ;
 p -> sec_serv = sec_serv_auth ;
 }