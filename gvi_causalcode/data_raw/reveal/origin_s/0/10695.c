kadm5_ret_t kadm5_create_policy ( void * server_handle , kadm5_policy_ent_t entry , long mask ) {
 CHECK_HANDLE ( server_handle ) ;
 krb5_clear_error_message ( ( ( kadm5_server_handle_t ) server_handle ) -> context ) ;
 if ( mask & KADM5_REF_COUNT ) return KADM5_BAD_MASK ;
 else return kadm5_create_policy_internal ( server_handle , entry , mask ) ;
 }