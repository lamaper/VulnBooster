static void dissect_zcl_color_control_move_to_hue ( tvbuff_t * tvb , proto_tree * tree , guint * offset , gboolean enhanced ) {
 if ( enhanced ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_enhanced_hue , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }
 else {
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_hue , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 }
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_direction , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_transit_time , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }