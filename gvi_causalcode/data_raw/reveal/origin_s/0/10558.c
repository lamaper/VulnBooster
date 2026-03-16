static void test_master_service_settings_cache ( void ) {
 int i , j ;
 for ( i = 1 ;
 i < 4 ;
 i ++ ) {
 cache = master_service_settings_cache_init ( master_service , "module" , "service_name" ) ;
 output . service_uses_local = ( i & 1 ) != 0 ;
 output . service_uses_remote = ( i & 2 ) != 0 ;
 for ( j = 0 ;
 j < 1000 ;
 j ++ ) test_master_service_settings_cache_once ( ) ;
 master_service_settings_cache_deinit ( & cache ) ;
 }
 }