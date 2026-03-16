static int dissect_rsl_ie_resource_inf ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint8 ie_id ;
 guint length ;
 int ie_offset ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_RESOURCE_INF ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_resource_inf , & ti , "Resource Information IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 ie_offset = offset ;
 while ( length > 0 ) {
 proto_tree_add_item ( ie_tree , hf_rsl_ch_no_Cbits , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ch_no_TN , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_interf_band , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_interf_band_reserved , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = length - 2 ;
 }
 return ie_offset + length ;
 }