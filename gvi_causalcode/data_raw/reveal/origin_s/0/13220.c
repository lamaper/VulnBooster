static void decode_ber_add_to_list ( gpointer key , gpointer value , gpointer user_data ) {
 struct ber_decode_as_populate * populate = ( struct ber_decode_as_populate * ) user_data ;
 populate -> add_to_list ( "ASN.1" , ( gchar * ) key , value , populate -> ui_element ) ;
 }