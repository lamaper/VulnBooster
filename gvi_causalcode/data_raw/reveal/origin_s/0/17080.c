static void dissect_zcl_color_control_color_loop_set ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 static const int * color_loop_update_fields [ ] = {
 & hf_zbee_zcl_color_control_color_loop_update_action , & hf_zbee_zcl_color_control_color_loop_update_direction , & hf_zbee_zcl_color_control_color_loop_update_time , & hf_zbee_zcl_color_control_color_loop_update_start_hue , NULL }
 ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_color_control_color_loop_update_flags , ett_zbee_zcl_color_control_color_loop_settings , color_loop_update_fields , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_color_loop_action , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_color_loop_direction , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_color_loop_time , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_color_loop_start_hue , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }