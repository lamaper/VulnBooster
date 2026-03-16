static void dissect_coap_opt_uri_host ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , coap_info * coinfo , int hf ) {
 const guint8 * str ;
 proto_tree_add_item_ret_string ( subtree , hf , tvb , offset , opt_length , ENC_ASCII , wmem_packet_scope ( ) , & str ) ;
 proto_item_append_text ( head_item , ": %s" , str ) ;
 if ( strchr ( str , ':' ) == NULL ) {
 wmem_strbuf_append_printf ( coinfo -> uri_str_strbuf , "coap://%s" , str ) ;
 }
 else {
 wmem_strbuf_append_printf ( coinfo -> uri_str_strbuf , "coap://[%s]" , str ) ;
 }
 }