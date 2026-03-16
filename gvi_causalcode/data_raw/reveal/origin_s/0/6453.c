static gint handle_message_connect ( tvbuff_t * tvb , packet_info * pinfo , gint offset , proto_tree * message_tree ) {
 guint8 the_one_byte ;
 the_one_byte = tvb_get_guint8 ( tvb , offset ) ;
 if ( 0 == the_one_byte ) {
 col_set_str ( pinfo -> cinfo , COL_INFO , "CONNECT-initial byte" ) ;
 proto_tree_add_item ( message_tree , hf_alljoyn_connect_byte_value , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 }
 return offset ;
 }