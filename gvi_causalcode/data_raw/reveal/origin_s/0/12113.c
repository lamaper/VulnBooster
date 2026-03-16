static guint16 de_tp_loop_type ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guchar oct ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_channel_coding03 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_loop_mechanism1C , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( ( oct & 0x1c ) == 0 ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_timeslot_number , tvb , curr_offset , 1 , ENC_NA ) ;
 }
 curr_offset += 1 ;
 return ( curr_offset - offset ) ;
 }