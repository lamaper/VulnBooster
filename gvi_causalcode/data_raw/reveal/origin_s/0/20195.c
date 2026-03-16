static PK11SymKey * import_symmetric_key ( struct crypto_instance * instance , enum sym_key_type key_type ) {
 SECItem key_item ;
 PK11SlotInfo * slot ;
 PK11SymKey * res_key ;
 CK_MECHANISM_TYPE cipher ;
 CK_ATTRIBUTE_TYPE operation ;
 CK_MECHANISM_TYPE wrap_mechanism ;
 int wrap_key_len ;
 PK11SymKey * wrap_key ;
 PK11Context * wrap_key_crypt_context ;
 SECItem tmp_sec_item ;
 SECItem wrapped_key ;
 int wrapped_key_len ;
 unsigned char wrapped_key_data [ MAX_WRAPPED_KEY_LEN ] ;
 int case_processed ;
 memset ( & key_item , 0 , sizeof ( key_item ) ) ;
 slot = NULL ;
 wrap_key = NULL ;
 res_key = NULL ;
 wrap_key_crypt_context = NULL ;
 key_item . type = siBuffer ;
 key_item . data = instance -> private_key ;
 case_processed = 0 ;
 switch ( key_type ) {
 case SYM_KEY_TYPE_CRYPT : key_item . len = cipher_key_len [ instance -> crypto_cipher_type ] ;
 cipher = cipher_to_nss [ instance -> crypto_cipher_type ] ;
 operation = CKA_ENCRYPT | CKA_DECRYPT ;
 case_processed = 1 ;
 break ;
 case SYM_KEY_TYPE_HASH : key_item . len = instance -> private_key_len ;
 cipher = hash_to_nss [ instance -> crypto_hash_type ] ;
 operation = CKA_SIGN ;
 case_processed = 1 ;
 break ;
 }
 if ( ! case_processed ) {
 log_printf ( instance -> log_level_error , "Unknown key_type" ) ;
 goto exit_res_key ;
 }
 slot = PK11_GetBestSlot ( cipher , NULL ) ;
 if ( slot == NULL ) {
 log_printf ( instance -> log_level_security , "Unable to find security slot (%d): %s" , PR_GetError ( ) , PR_ErrorToString ( PR_GetError ( ) , PR_LANGUAGE_I_DEFAULT ) ) ;
 goto exit_res_key ;
 }
 wrap_mechanism = PK11_GetBestWrapMechanism ( slot ) ;
 wrap_key_len = PK11_GetBestKeyLength ( slot , wrap_mechanism ) ;
 wrap_key = PK11_KeyGen ( slot , wrap_mechanism , NULL , wrap_key_len , NULL ) ;
 if ( wrap_key == NULL ) {
 log_printf ( instance -> log_level_security , "Unable to generate wrapping key (%d): %s" , PR_GetError ( ) , PR_ErrorToString ( PR_GetError ( ) , PR_LANGUAGE_I_DEFAULT ) ) ;
 goto exit_res_key ;
 }
 memset ( & tmp_sec_item , 0 , sizeof ( tmp_sec_item ) ) ;
 wrap_key_crypt_context = PK11_CreateContextBySymKey ( wrap_mechanism , CKA_ENCRYPT , wrap_key , & tmp_sec_item ) ;
 if ( wrap_key_crypt_context == NULL ) {
 log_printf ( instance -> log_level_security , "Unable to create encrypt context (%d): %s" , PR_GetError ( ) , PR_ErrorToString ( PR_GetError ( ) , PR_LANGUAGE_I_DEFAULT ) ) ;
 goto exit_res_key ;
 }
 wrapped_key_len = ( int ) sizeof ( wrapped_key_data ) ;
 if ( PK11_CipherOp ( wrap_key_crypt_context , wrapped_key_data , & wrapped_key_len , sizeof ( wrapped_key_data ) , key_item . data , key_item . len ) != SECSuccess ) {
 log_printf ( instance -> log_level_security , "Unable to encrypt authkey (%d): %s" , PR_GetError ( ) , PR_ErrorToString ( PR_GetError ( ) , PR_LANGUAGE_I_DEFAULT ) ) ;
 goto exit_res_key ;
 }
 if ( PK11_Finalize ( wrap_key_crypt_context ) != SECSuccess ) {
 log_printf ( instance -> log_level_security , "Unable to finalize encryption of authkey (%d): %s" , PR_GetError ( ) , PR_ErrorToString ( PR_GetError ( ) , PR_LANGUAGE_I_DEFAULT ) ) ;
 goto exit_res_key ;
 }
 memset ( & tmp_sec_item , 0 , sizeof ( tmp_sec_item ) ) ;
 wrapped_key . data = wrapped_key_data ;
 wrapped_key . len = wrapped_key_len ;
 res_key = PK11_UnwrapSymKey ( wrap_key , wrap_mechanism , & tmp_sec_item , & wrapped_key , cipher , operation , key_item . len ) ;
 if ( res_key == NULL ) {
 log_printf ( instance -> log_level_security , "Failure to import key into NSS (%d): %s" , PR_GetError ( ) , PR_ErrorToString ( PR_GetError ( ) , PR_LANGUAGE_I_DEFAULT ) ) ;
 goto exit_res_key ;
 }
 exit_res_key : if ( wrap_key_crypt_context != NULL ) {
 PK11_DestroyContext ( wrap_key_crypt_context , PR_TRUE ) ;
 }
 if ( wrap_key != NULL ) {
 PK11_FreeSymKey ( wrap_key ) ;
 }
 if ( slot != NULL ) {
 PK11_FreeSlot ( slot ) ;
 }
 return ( res_key ) ;
 }