static int dissect_rsl_ie_sys_info_type ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory , guint8 * sys_info_type ) {
 proto_tree * ie_tree ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_SYS_INFO_TYPE ) {
 * sys_info_type = 0xff ;
 return offset ;
 }
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 2 , ett_ie_sys_info_type , NULL , "System Info Type IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 * sys_info_type = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_rsl_sys_info_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }