static guint16 de_tp_rlc_sdu_counter_value ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_ue_received_rlc_sdu_counter_value , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 curr_offset += 4 ;
 return ( curr_offset - offset ) ;
 }