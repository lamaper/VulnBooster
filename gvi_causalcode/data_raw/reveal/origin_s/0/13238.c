void ber_decode_as_foreach ( GHFunc func , gpointer user_data ) {
 da_data decode_as_data ;
 decode_as_data . func = func ;
 decode_as_data . user_data = user_data ;
 dissector_table_foreach ( "ber.syntax" , ber_decode_as_dt , & decode_as_data ) ;
 }