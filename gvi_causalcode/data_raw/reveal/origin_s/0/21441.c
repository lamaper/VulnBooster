static void dissect_zcl_groups_add_group_or_if_identifying ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint attr_uint ;
 guint8 * attr_string ;
 proto_tree_add_item ( tree , hf_zbee_zcl_groups_group_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 attr_uint = tvb_get_guint8 ( tvb , * offset ) ;
 if ( attr_uint == 0xff ) attr_uint = 0 ;
 proto_tree_add_uint ( tree , hf_zbee_zcl_groups_attr_str_len , tvb , * offset , 1 , attr_uint ) ;
 * offset += 1 ;
 attr_string = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , * offset , attr_uint , ENC_ASCII ) ;
 proto_item_append_text ( tree , ", String: %s" , attr_string ) ;
 proto_tree_add_string ( tree , hf_zbee_zcl_groups_attr_str , tvb , * offset , attr_uint , attr_string ) ;
 * offset += attr_uint ;
 }