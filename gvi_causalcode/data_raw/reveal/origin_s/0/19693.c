static void gsm_a_stat_init ( new_stat_tap_ui * new_stat , new_stat_tap_gui_init_cb gui_callback , void * gui_data , const char * table_title , const value_string * msg_strings ) {
 int num_fields = sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) ;
 new_stat_tap_table * table ;
 guint i ;
 stat_tap_table_item_type items [ sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) ] ;
 items [ IEI_COLUMN ] . type = TABLE_ITEM_UINT ;
 items [ MSG_NAME_COLUMN ] . type = TABLE_ITEM_STRING ;
 items [ COUNT_COLUMN ] . type = TABLE_ITEM_UINT ;
 items [ COUNT_COLUMN ] . value . uint_value = 0 ;
 table = new_stat_tap_init_table ( table_title , num_fields , 0 , NULL , gui_callback , gui_data ) ;
 new_stat_tap_add_table ( new_stat , table ) ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 const char * msg_str = try_val_to_str ( i , msg_strings ) ;
 char * col_str ;
 if ( msg_str ) {
 col_str = g_strdup ( msg_str ) ;
 }
 else {
 col_str = g_strdup_printf ( "Unknown message %d" , i ) ;
 }
 items [ IEI_COLUMN ] . value . uint_value = i ;
 items [ MSG_NAME_COLUMN ] . value . string_value = col_str ;
 new_stat_tap_init_table_row ( table , i , num_fields , items ) ;
 }
 }