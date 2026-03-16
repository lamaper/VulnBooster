static void gsm_a_sacch_rr_stat_init ( new_stat_tap_ui * new_stat , new_stat_tap_gui_init_cb gui_callback , void * gui_data ) {
 gsm_a_stat_init ( new_stat , gui_callback , gui_data , "GSM A-I/F SACCH Statistics" , gsm_a_rr_short_pd_msg_strings ) ;
 }