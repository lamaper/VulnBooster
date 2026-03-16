gcry_error_t gcry_pk_decrypt ( gcry_sexp_t * r_plain , gcry_sexp_t s_data , gcry_sexp_t s_skey ) {
 gcry_mpi_t * skey = NULL , * data = NULL , plain = NULL ;
 unsigned char * unpad = NULL ;
 size_t unpadlen = 0 ;
 int modern , flags ;
 struct pk_encoding_ctx ctx ;
 gcry_err_code_t rc ;
 gcry_module_t module_enc = NULL , module_key = NULL ;
 * r_plain = NULL ;
 ctx . label = NULL ;
 REGISTER_DEFAULT_PUBKEYS ;
 rc = sexp_to_key ( s_skey , 1 , GCRY_PK_USAGE_ENCR , NULL , & skey , & module_key , NULL ) ;
 if ( rc ) goto leave ;
 init_encoding_ctx ( & ctx , PUBKEY_OP_DECRYPT , gcry_pk_get_nbits ( s_skey ) ) ;
 rc = sexp_to_enc ( s_data , & data , & module_enc , & modern , & flags , & ctx ) ;
 if ( rc ) goto leave ;
 if ( module_key -> mod_id != module_enc -> mod_id ) {
 rc = GPG_ERR_CONFLICT ;
 goto leave ;
 }
 rc = pubkey_decrypt ( module_key -> mod_id , & plain , data , skey , flags ) ;
 if ( rc ) goto leave ;
 switch ( ctx . encoding ) {
 case PUBKEY_ENC_PKCS1 : rc = pkcs1_decode_for_encryption ( & unpad , & unpadlen , gcry_pk_get_nbits ( s_skey ) , plain ) ;
 mpi_free ( plain ) ;
 plain = NULL ;
 if ( ! rc ) rc = gcry_err_code ( gcry_sexp_build ( r_plain , NULL , "(value %b)" , ( int ) unpadlen , unpad ) ) ;
 break ;
 case PUBKEY_ENC_OAEP : rc = oaep_decode ( & unpad , & unpadlen , gcry_pk_get_nbits ( s_skey ) , ctx . hash_algo , plain , ctx . label , ctx . labellen ) ;
 mpi_free ( plain ) ;
 plain = NULL ;
 if ( ! rc ) rc = gcry_err_code ( gcry_sexp_build ( r_plain , NULL , "(value %b)" , ( int ) unpadlen , unpad ) ) ;
 break ;
 default : rc = gcry_err_code ( gcry_sexp_build ( r_plain , NULL , modern ? "(value %m)" : "%m" , plain ) ) ;
 break ;
 }
 leave : gcry_free ( unpad ) ;
 if ( skey ) {
 release_mpi_array ( skey ) ;
 gcry_free ( skey ) ;
 }
 mpi_free ( plain ) ;
 if ( data ) {
 release_mpi_array ( data ) ;
 gcry_free ( data ) ;
 }
 if ( module_key || module_enc ) {
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 if ( module_key ) _gcry_module_release ( module_key ) ;
 if ( module_enc ) _gcry_module_release ( module_enc ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 }
 gcry_free ( ctx . label ) ;
 return gcry_error ( rc ) ;
 }