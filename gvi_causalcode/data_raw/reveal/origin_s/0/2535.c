static bool login_settings_check ( void * _set , pool_t pool , const char * * error_r ATTR_UNUSED ) {
 struct login_settings * set = _set ;
 set -> log_format_elements_split = p_strsplit ( pool , set -> login_log_format_elements , " " ) ;
 if ( set -> auth_debug_passwords ) set -> auth_debug = TRUE ;
 if ( set -> auth_debug ) set -> auth_verbose = TRUE ;
 return TRUE ;
 }