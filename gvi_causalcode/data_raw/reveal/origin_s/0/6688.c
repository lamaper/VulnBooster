static int dissect_rsl_ie_ms_timing_offset ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_tree * ie_tree ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_FULL_MS_TIMING_OFFSET ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_ms_timing_offset , NULL , "MS Timing Offset IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_timing_offset , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }