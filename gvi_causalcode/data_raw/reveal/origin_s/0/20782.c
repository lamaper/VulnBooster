static void dissect_coap_opt_hex_string ( tvbuff_t * tvb , proto_item * item , proto_tree * subtree , gint offset , gint opt_length , int hf ) {
 const guint8 * str ;
 if ( opt_length == 0 ) str = nullstr ;
 else str = tvb_bytes_to_str_punct ( wmem_packet_scope ( ) , tvb , offset , opt_length , ' ' ) ;
 proto_tree_add_item ( subtree , hf , tvb , offset , opt_length , ENC_NA ) ;
 proto_item_append_text ( item , ": %s" , str ) ;
 }