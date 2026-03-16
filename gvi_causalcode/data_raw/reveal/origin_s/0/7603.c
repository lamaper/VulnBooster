static kadm5_ret_t validate_allowed_keysalts ( const char * allowed_keysalts ) {
 kadm5_ret_t ret ;
 krb5_key_salt_tuple * ks_tuple = NULL ;
 krb5_int32 n_ks_tuple = 0 ;
 if ( strchr ( allowed_keysalts , '\t' ) != NULL ) return KADM5_BAD_KEYSALTS ;
 ret = krb5_string_to_keysalts ( allowed_keysalts , "," , ":.-" , 0 , & ks_tuple , & n_ks_tuple ) ;
 free ( ks_tuple ) ;
 if ( ret == EINVAL ) return KADM5_BAD_KEYSALTS ;
 return ret ;
 }