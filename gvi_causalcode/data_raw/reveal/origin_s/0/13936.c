static void h223_lc_init ( void ) {
 h223_lc_init_dir ( P2P_DIR_SENT ) ;
 h223_lc_init_dir ( P2P_DIR_RECV ) ;
 h223_lc_params_temp = NULL ;
 h245_lc_dissector = NULL ;
 h223_fw_lc_num = 0 ;
 }