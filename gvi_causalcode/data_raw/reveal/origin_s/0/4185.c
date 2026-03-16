static void dissect_coap_opt_ctype ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , int hf , coap_info * coinfo ) {
 if ( opt_length == 0 ) {
 coinfo -> ctype_value = 0 ;
 }
 else {
 coinfo -> ctype_value = coap_get_opt_uint ( tvb , offset , opt_length ) ;
 }
 coinfo -> ctype_str = val_to_str ( coinfo -> ctype_value , vals_ctype , "Unknown Type %u" ) ;
 proto_tree_add_string ( subtree , hf , tvb , offset , opt_length , coinfo -> ctype_str ) ;
 proto_item_append_text ( head_item , ": %s" , coinfo -> ctype_str ) ;
 }