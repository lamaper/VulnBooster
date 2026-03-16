static void gsm_a_bssmap_stat_init ( new_stat_tap_ui * new_stat , new_stat_tap_gui_init_cb gui_callback , void * gui_data ) {
 gsm_a_stat_init ( new_stat , gui_callback , gui_data , "GSM A-I/F BSSMAP Statistics" , gsm_a_bssmap_msg_strings ) ;
 }