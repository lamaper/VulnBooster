static guint16 de_tp_loop_ack ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_channel_coding30 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_loop_mechanism0E , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_multislot_tch , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset += 1 ;
 return ( curr_offset - offset ) ;
 }