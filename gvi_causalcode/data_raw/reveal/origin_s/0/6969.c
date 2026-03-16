static int dissect_rsl_ie_rtd ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * rtd_item ;
 proto_tree * ie_tree ;
 guint8 ie_id ;
 guint8 rtd ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_RTD ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_rtd , NULL , "Round Trip Delay IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 rtd = ( tvb_get_guint8 ( tvb , offset ) >> 1 ) * 20 ;
 rtd_item = proto_tree_add_uint ( tree , hf_rsl_rtd , tvb , offset , 1 , rtd ) ;
 proto_item_append_text ( rtd_item , " ms" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_delay_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }