static guint16 de_tp_epc_ue_tl_b_lb_setup ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_ue_tl_b_ip_pdu_delay , tvb , curr_offset << 3 , 8 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }