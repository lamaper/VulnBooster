static void add_h245_Address ( h323_calls_info_t * h323info , h245_address_t * h245_address ) {
 h323info -> h245_list = g_list_prepend ( h323info -> h245_list , h245_address ) ;
 }