static void gsm_a_stat_free_table_item ( new_stat_tap_table * table _U_ , guint row _U_ , guint column , stat_tap_table_item_type * field_data ) {
 if ( column != MSG_NAME_COLUMN ) return ;
 g_free ( ( char * ) field_data -> value . string_value ) ;
 }