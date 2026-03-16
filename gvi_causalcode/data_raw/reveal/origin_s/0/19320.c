static int dissect_rsl_ie_act_type ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_tree * ie_tree ;
 guint8 ie_id ;
 guint octet ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_ACT_TYPE ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 2 , ett_ie_act_type , NULL , "Activation Type IE " ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_rbit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 octet = ( tvb_get_guint8 ( tvb , offset ) & 0x06 ) >> 1 ;
 proto_tree_add_item ( ie_tree , hf_rsl_a3a2 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 switch ( octet ) {
 case 0 : proto_tree_add_item ( ie_tree , hf_rsl_a1_0 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 case 1 : proto_tree_add_item ( ie_tree , hf_rsl_a1_1 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 case 2 : proto_tree_add_item ( ie_tree , hf_rsl_a1_2 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 default : break ;
 }
 offset ++ ;
 return offset ;
 }