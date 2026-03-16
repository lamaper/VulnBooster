static void dissect_coap_opt_proxy_uri ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , int hf ) {
 const guint8 * str = NULL ;
 if ( opt_length == 0 ) {
 str = nullstr ;
 }
 else {
 str = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , opt_length , ENC_ASCII ) ;
 }
 proto_tree_add_string ( subtree , hf , tvb , offset , opt_length , str ) ;
 proto_item_append_text ( head_item , ": %s" , str ) ;
 }