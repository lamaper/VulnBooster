static int dissect_rsl_ie_bs_power ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_tree * ie_tree ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_BS_POW ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 2 , ett_ie_bs_power , NULL , "BS Power IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_epc_mode , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_bs_fpc_epc_mode , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_bs_power , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }