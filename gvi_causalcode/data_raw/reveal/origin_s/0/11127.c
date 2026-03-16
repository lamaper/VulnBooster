static int dissect_rsl_ie_ch_mode ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint8 length ;
 int ie_offset ;
 guint8 ie_id ;
 guint8 octet ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_CH_MODE ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_ch_mode , & ti , "Channel Mode IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 ie_offset = offset ;
 proto_tree_add_item ( ie_tree , hf_rsl_cm_dtxd , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_cm_dtxu , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_speech_or_data , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_ch_rate_and_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 switch ( octet ) {
 case 1 : proto_tree_add_item ( ie_tree , hf_rsl_speech_coding_alg , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 case 2 : proto_tree_add_item ( ie_tree , hf_rsl_extension_bit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_t_nt_bit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( octet & 0x40 ) == 0x40 ) {
 proto_tree_add_item ( ie_tree , hf_rsl_ra_if_data_rte , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( ie_tree , hf_rsl_data_rte , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 break ;
 case 3 : proto_tree_add_item ( ie_tree , hf_rsl_no_resources_required , tvb , offset , 1 , ENC_NA ) ;
 break ;
 default : proto_tree_add_expert ( ie_tree , pinfo , & ei_rsl_speech_or_data_indicator , tvb , offset , 1 ) ;
 break ;
 }
 offset ++ ;
 return ie_offset + length ;
 }