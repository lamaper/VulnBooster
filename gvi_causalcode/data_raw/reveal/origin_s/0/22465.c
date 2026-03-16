static int dissect_rsl_ie_ch_id ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint8 length ;
 int ie_offset ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_CH_ID ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_ch_id , & ti , "Channel Identification IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 ie_offset = offset ;
 proto_tree_add_item ( ie_tree , hf_rsl_channel_description_tag , tvb , offset , 1 , ENC_NA ) ;
 de_rr_ch_dsc ( tvb , ie_tree , pinfo , offset + 1 , length , NULL , 0 ) ;
 offset += 4 ;
 proto_tree_add_item ( ie_tree , hf_rsl_mobile_allocation_tag , tvb , offset , 2 , ENC_NA ) ;
 return ie_offset + length ;
 }