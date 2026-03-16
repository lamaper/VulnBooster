static int dissect_rsl_ie_link_id ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_tree * ie_tree ;
 guint8 octet ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_LINK_ID ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 2 , ett_ie_link_id , NULL , "Link Identifier IE " ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( octet & 0x20 ) == 0x20 ) {
 proto_tree_add_item ( ie_tree , hf_rsl_na , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }
 proto_tree_add_item ( ie_tree , hf_rsl_ch_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_na , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_prio , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_sapi , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }