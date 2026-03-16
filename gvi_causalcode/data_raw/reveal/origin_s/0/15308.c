static void unlock_princ ( kadm5_principal_ent_t princ , long * mask , const char * caller ) {
 krb5_error_code retval ;
 krb5_timestamp now ;
 krb5_octet timebuf [ 4 ] ;
 princ -> fail_auth_count = 0 ;
 * mask |= KADM5_FAIL_AUTH_COUNT ;
 retval = krb5_timeofday ( context , & now ) ;
 if ( retval ) {
 com_err ( caller , retval , _ ( "while getting time" ) ) ;
 exit ( 1 ) ;
 }
 store_32_le ( ( krb5_int32 ) now , timebuf ) ;
 add_tl_data ( & princ -> n_tl_data , & princ -> tl_data , KRB5_TL_LAST_ADMIN_UNLOCK , 4 , timebuf ) ;
 * mask |= KADM5_TL_DATA ;
 }