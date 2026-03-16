gcry_err_code_t _gcry_pubkey_get_sexp ( gcry_sexp_t * r_sexp , int mode , gcry_ctx_t ctx ) {
 mpi_ec_t ec ;
 if ( ! r_sexp ) return GPG_ERR_INV_VALUE ;
 * r_sexp = NULL ;
 switch ( mode ) {
 case 0 : case GCRY_PK_GET_PUBKEY : case GCRY_PK_GET_SECKEY : break ;
 default : return GPG_ERR_INV_VALUE ;
 }
 if ( ! ctx ) return GPG_ERR_NO_CRYPT_CTX ;
 ec = _gcry_ctx_find_pointer ( ctx , CONTEXT_TYPE_EC ) ;
 if ( ec ) return _gcry_pk_ecc_get_sexp ( r_sexp , mode , ec ) ;
 return GPG_ERR_WRONG_CRYPT_CTX ;
 }