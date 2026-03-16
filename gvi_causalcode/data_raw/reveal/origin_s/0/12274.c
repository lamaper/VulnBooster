static void ber_populate_list ( const gchar * table_name _U_ , decode_as_add_to_list_func add_to_list , gpointer ui_element ) {
 struct ber_decode_as_populate populate ;
 populate . add_to_list = add_to_list ;
 populate . ui_element = ui_element ;
 ber_decode_as_foreach ( decode_ber_add_to_list , & populate ) ;
 }