static void dissect_zcl_color_control_move_hue_saturation ( tvbuff_t * tvb , proto_tree * tree , guint * offset , gboolean enhanced ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_move_mode , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 if ( enhanced ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_enhanced_rate , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }
 else {
 proto_tree_add_item ( tree , hf_zbee_zcl_color_control_rate , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 }
 }