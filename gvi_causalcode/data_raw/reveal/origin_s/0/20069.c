static int dissect_rsl_ie_multirate_conf ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint length ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_MULTIRATE_CONF ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_multirate_conf , & ti , "MultiRate configuration IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 de_rr_multirate_conf ( tvb , ie_tree , pinfo , offset , length , NULL , 0 ) ;
 offset = offset + length ;
 return offset ;
 }