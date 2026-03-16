int main ( void ) {
 static void ( * test_functions [ ] ) ( void ) = {
 test_master_service_settings_cache , NULL }
 ;
 pool_t pool ;
 int ret ;
 i_zero ( & input ) ;
 input . module = "module" ;
 input . service = "service_name" ;
 set . config_cache_size = 1024 * 4 ;
 pool = pool_alloconly_create ( "set pool" , 1024 ) ;
 test_master_service . set_parser = settings_parser_init ( pool , & test_setting_parser_info , 0 ) ;
 master_service = & test_master_service ;
 ret = test_run ( test_functions ) ;
 settings_parser_deinit ( & test_master_service . set_parser ) ;
 pool_unref ( & pool ) ;
 return ret ;
 }