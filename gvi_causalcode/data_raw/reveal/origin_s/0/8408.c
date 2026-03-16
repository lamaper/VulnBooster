static int dissect_rsl_ie_rach_load ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint length ;
 guint8 ie_id ;
 int ie_offset ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_RACH_LOAD ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_rach_load , & ti , "RACH Load IE " ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 ie_offset = offset ;
 proto_tree_add_item ( ie_tree , hf_rsl_rach_slot_cnt , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 length = length - 2 ;
 proto_tree_add_item ( ie_tree , hf_rsl_rach_busy_cnt , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 length = length - 2 ;
 proto_tree_add_item ( ie_tree , hf_rsl_rach_acc_cnt , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 length = length - 2 ;
 if ( length > 0 ) {
 proto_tree_add_item ( ie_tree , hf_rsl_rach_supplementary_information , tvb , offset , length , ENC_NA ) ;
 }
 offset = ie_offset + length ;
 return offset ;
 }