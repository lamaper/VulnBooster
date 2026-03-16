static int myisam_init ( void * p ) {
 handlerton * myisam_hton ;


 else myisam_recover_options = HA_RECOVER_OFF ;
 myisam_block_size = ( uint ) 1 << my_bit_log2 ( opt_myisam_block_size ) ;
 myisam_hton = ( handlerton * ) p ;
 myisam_hton -> state = SHOW_OPTION_YES ;
 myisam_hton -> db_type = DB_TYPE_MYISAM ;
 myisam_hton -> create = myisam_create_handler ;
 myisam_hton -> panic = myisam_panic ;
 myisam_hton -> flags = HTON_CAN_RECREATE | HTON_SUPPORT_LOG_TABLES ;
 myisam_hton -> is_supported_system_table = myisam_is_supported_system_table ;
 return 0 ;
 }