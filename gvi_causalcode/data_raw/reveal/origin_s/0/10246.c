static guint16 de_tp_pdu_description ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint16 value ;
 curr_offset = offset ;
 value = tvb_get_ntohs ( tvb , curr_offset ) ;
 curr_offset += 2 ;
 if ( value & 0x8000 ) {
 if ( ( value & 0xfff ) == 0 ) proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_tp_pdu_description , tvb , curr_offset , 2 , value , "Infinite number of PDUs to be transmitted in the TBF" ) ;
 else proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_tp_pdu_description , tvb , curr_offset , 2 , value & 0xfff , "%d PDUs to be transmitted in the TBF" , value & 0xfff ) ;
 }
 else proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_tp_pdu_description , tvb , curr_offset , 2 , value , "reserved" ) ;
 return ( curr_offset - offset ) ;
 }