void crypto_policy_set_aes_cm_256_null_auth ( crypto_policy_t * p ) {
 p -> cipher_type = AES_ICM ;
 p -> cipher_key_len = 46 ;
 p -> auth_type = NULL_AUTH ;
 p -> auth_key_len = 0 ;
 p -> auth_tag_len = 0 ;
 p -> sec_serv = sec_serv_conf ;
 }