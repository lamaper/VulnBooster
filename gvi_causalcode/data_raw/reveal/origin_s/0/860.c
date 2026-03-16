static void dissect_coap_opt_uint ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , int hf ) {
 guint i = 0 ;
 if ( opt_length != 0 ) {
 i = coap_get_opt_uint ( tvb , offset , opt_length ) ;
 }
 proto_tree_add_uint ( subtree , hf , tvb , offset , opt_length , i ) ;
 proto_item_append_text ( head_item , ": %u" , i ) ;
 }