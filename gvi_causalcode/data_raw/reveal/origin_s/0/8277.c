SRP_user_pwd * SRP_VBASE_get1_by_user ( SRP_VBASE * vb , char * username ) {
 SRP_user_pwd * user ;
 unsigned char digv [ SHA_DIGEST_LENGTH ] ;
 unsigned char digs [ SHA_DIGEST_LENGTH ] ;
 EVP_MD_CTX ctxt ;
 if ( vb == NULL ) return NULL ;
 if ( ( user = find_user ( vb , username ) ) != NULL ) return srp_user_pwd_dup ( user ) ;
 if ( ( vb -> seed_key == NULL ) || ( vb -> default_g == NULL ) || ( vb -> default_N == NULL ) ) return NULL ;
 if ( ( user = SRP_user_pwd_new ( ) ) == NULL ) return NULL ;
 SRP_user_pwd_set_gN ( user , vb -> default_g , vb -> default_N ) ;
 if ( ! SRP_user_pwd_set_ids ( user , username , NULL ) ) goto err ;
 if ( RAND_pseudo_bytes ( digv , SHA_DIGEST_LENGTH ) < 0 ) goto err ;
 EVP_MD_CTX_init ( & ctxt ) ;
 EVP_DigestInit_ex ( & ctxt , EVP_sha1 ( ) , NULL ) ;
 EVP_DigestUpdate ( & ctxt , vb -> seed_key , strlen ( vb -> seed_key ) ) ;
 EVP_DigestUpdate ( & ctxt , username , strlen ( username ) ) ;
 EVP_DigestFinal_ex ( & ctxt , digs , NULL ) ;
 EVP_MD_CTX_cleanup ( & ctxt ) ;
 if ( SRP_user_pwd_set_sv_BN ( user , BN_bin2bn ( digs , SHA_DIGEST_LENGTH , NULL ) , BN_bin2bn ( digv , SHA_DIGEST_LENGTH , NULL ) ) ) return user ;
 err : SRP_user_pwd_free ( user ) ;
 return NULL ;
 }