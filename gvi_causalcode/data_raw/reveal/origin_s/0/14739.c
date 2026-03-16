static void restrict_update_of_old_passwords_var ( THD * thd , enum_var_type var_type ) {
 if ( var_type == OPT_GLOBAL ) {
 pthread_mutex_lock ( & LOCK_global_system_variables ) ;
 global_system_variables . old_passwords = 1 ;
 pthread_mutex_unlock ( & LOCK_global_system_variables ) ;
 }
 else thd -> variables . old_passwords = 1 ;
 }