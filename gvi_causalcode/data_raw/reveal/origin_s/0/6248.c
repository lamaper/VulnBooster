static void ber_decode_as_dt ( const gchar * table_name _U_ , ftenum_t selector_type _U_ , gpointer key , gpointer value , gpointer user_data ) {
 da_data * decode_as_data ;
 decode_as_data = ( da_data * ) user_data ;
 decode_as_data -> func ( key , value , decode_as_data -> user_data ) ;
 }