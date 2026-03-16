static void test_master_service_settings_cache_once ( void ) {
 const struct setting_parser_context * parser ;
 const char * error ;
 output . used_local = output . service_uses_local && rand ( ) % 2 ;
 if ( output . used_local ) {
 input . local_ip . family = AF_INET ;
 input . local_ip . u . ip4 . s_addr = 100 + rand ( ) % 100 ;
 }
 output . used_remote = output . service_uses_remote && rand ( ) % 2 ;
 if ( output . used_remote ) {
 input . remote_ip . family = AF_INET ;
 input . remote_ip . u . ip4 . s_addr = 100 + rand ( ) % 100 ;
 }
 test_assert ( master_service_settings_cache_read ( cache , & input , NULL , & parser , & error ) == 0 ) ;
 }