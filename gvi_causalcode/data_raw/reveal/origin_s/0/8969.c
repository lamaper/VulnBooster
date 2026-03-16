static guint16 de_tp_egprs_mode_flag ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_egprs_mode_flag , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_downlink_timeslot_offset , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset += 1 ;
 return ( curr_offset - offset ) ;
 }