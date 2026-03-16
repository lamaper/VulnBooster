static void gsm_a_stat_reset ( new_stat_tap_table * table ) {
 guint element ;
 stat_tap_table_item_type * item_data ;
 for ( element = 0 ;
 element < table -> num_elements ;
 element ++ ) {
 item_data = new_stat_tap_get_field_data ( table , element , COUNT_COLUMN ) ;
 item_data -> value . uint_value = 0 ;
 new_stat_tap_set_field_data ( table , element , COUNT_COLUMN , item_data ) ;
 }
 }