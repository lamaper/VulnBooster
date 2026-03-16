static void * login_setting_dup ( pool_t pool , const struct setting_parser_info * info , const void * src_set ) {
 const char * error ;
 void * dest ;
 dest = settings_dup ( info , src_set , pool ) ;
 if ( ! settings_check ( info , pool , dest , & error ) ) {
 const char * name = info -> module_name ;
 i_fatal ( "settings_check(%s) failed: %s" , name != NULL ? name : "unknown" , error ) ;
 }
 return dest ;
 }