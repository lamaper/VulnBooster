static void dissect_zcl_scenes_view_scene_response ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 status , * attr_string ;
 guint attr_uint ;
 status = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_status , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_group_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_scene_id , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 if ( status == ZBEE_ZCL_STAT_SUCCESS ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_transit_time , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 attr_uint = tvb_get_guint8 ( tvb , * offset ) ;
 if ( attr_uint == 0xff ) attr_uint = 0 ;
 proto_tree_add_uint ( tree , hf_zbee_zcl_scenes_attr_str_len , tvb , * offset , 1 , attr_uint ) ;
 * offset += 1 ;
 attr_string = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , * offset , attr_uint , ENC_ASCII ) ;
 proto_item_append_text ( tree , ", String: %s" , attr_string ) ;
 proto_tree_add_string ( tree , hf_zbee_zcl_scenes_attr_str , tvb , * offset , attr_uint , attr_string ) ;
 * offset += attr_uint ;
 proto_tree_add_item ( tree , hf_zbee_zcl_scenes_extension_set_field , tvb , * offset , - 1 , ENC_NA ) ;
 }
 }