static gint coap_opt_check ( packet_info * pinfo , proto_tree * subtree , guint opt_num , gint opt_length , coap_common_dissect_t * dissect_hf ) {
 int i ;
 for ( i = 0 ;
 i < ( int ) ( array_length ( coi ) ) ;
 i ++ ) {
 if ( coi [ i ] . type == opt_num ) break ;
 }
 if ( i == ( int ) ( array_length ( coi ) ) ) {
 expert_add_info_format ( pinfo , subtree , & dissect_hf -> ei . opt_invalid_number , "Invalid Option Number %u" , opt_num ) ;
 return - 1 ;
 }
 if ( opt_length < coi [ i ] . min || opt_length > coi [ i ] . max ) {
 expert_add_info_format ( pinfo , subtree , & dissect_hf -> ei . opt_invalid_range , "Invalid Option Range: %d (%d < x < %d)" , opt_length , coi [ i ] . min , coi [ i ] . max ) ;
 }
 return 0 ;
 }