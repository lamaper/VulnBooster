static void dissect_coap_opt_uri_port ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , coap_info * coinfo , int hf ) {
 guint port = 0 ;
 if ( opt_length != 0 ) {
 port = coap_get_opt_uint ( tvb , offset , opt_length ) ;
 }
 proto_tree_add_uint ( subtree , hf , tvb , offset , opt_length , port ) ;
 proto_item_append_text ( head_item , ": %u" , port ) ;
 wmem_strbuf_append_printf ( coinfo -> uri_str_strbuf , ":%u" , port ) ;
 }