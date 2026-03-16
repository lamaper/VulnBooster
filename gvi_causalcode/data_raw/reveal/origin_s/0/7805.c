static void gsm_a_dtap_cc_stat_init ( new_stat_tap_ui * new_stat , new_stat_tap_gui_init_cb gui_callback , void * gui_data ) {
 gsm_a_stat_init ( new_stat , gui_callback , gui_data , "GSM A-I/F DTAP Call Control Statistics" , gsm_a_dtap_msg_cc_strings ) ;
 }