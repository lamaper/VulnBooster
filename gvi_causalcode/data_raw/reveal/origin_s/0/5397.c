static guint16 de_tp_ack ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guchar oct ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 if ( ( oct & 0xF0 ) == 0x80 ) proto_tree_add_uint ( tree , hf_gsm_a_dtap_ack_element , tvb , curr_offset , 1 , oct & 0x01 ) ;
 else proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_ack_element , tvb , curr_offset , 1 , 0xFF , "No acknowledgment element present" ) ;
 curr_offset += 1 ;
 return ( curr_offset - offset ) ;
 }