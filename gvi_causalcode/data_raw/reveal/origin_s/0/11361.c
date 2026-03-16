static krb5_error_code create_princ ( kadm5_principal_ent_rec * princ , long mask , int n_ks , krb5_key_salt_tuple * ks , char * pass ) {
 if ( ks ) return kadm5_create_principal_3 ( handle , princ , mask , n_ks , ks , pass ) ;
 else return kadm5_create_principal ( handle , princ , mask , pass ) ;
 }