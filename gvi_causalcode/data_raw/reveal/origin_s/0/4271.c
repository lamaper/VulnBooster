static void dissect_coap_opt_uri_query ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , coap_info * coinfo , int hf ) {
 const guint8 * str = NULL ;
 wmem_strbuf_append_c ( coinfo -> uri_query_strbuf , ( wmem_strbuf_get_len ( coinfo -> uri_query_strbuf ) == 0 ) ? '?' : '&' ) ;
 if ( opt_length == 0 ) {
 str = nullstr ;
 }
 else {
 str = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , opt_length , ENC_ASCII ) ;
 wmem_strbuf_append ( coinfo -> uri_query_strbuf , str ) ;
 }
 proto_tree_add_string ( subtree , hf , tvb , offset , opt_length , str ) ;
 proto_item_append_text ( head_item , ": %s" , str ) ;
 }