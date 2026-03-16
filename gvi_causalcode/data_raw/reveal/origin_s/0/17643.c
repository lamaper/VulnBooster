static void dissect_zcl_part_trasfpartframe ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint8 options ;
 guint16 u16len ;
 guint8 frame_len ;
 static const int * part_opt [ ] = {
 & hf_zbee_zcl_part_opt_first_block , & hf_zbee_zcl_part_opt_indic_len , & hf_zbee_zcl_part_opt_res , NULL }
 ;
 options = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_part_opt , ett_zbee_zcl_part_fragm_options , part_opt , ENC_NA ) ;
 * offset += 1 ;
 if ( ( options & ZBEE_ZCL_PART_OPT_INDIC_LEN ) == 0 ) {
 u16len = ( guint16 ) tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_part_indicator , tvb , * offset , 1 , ( u16len & 0xFF ) ) ;
 * offset += 1 ;
 }
 else {
 u16len = tvb_get_letohs ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_part_indicator , tvb , * offset , 2 , u16len ) ;
 * offset += 2 ;
 }
 frame_len = tvb_get_guint8 ( tvb , * offset ) ;
 if ( frame_len == ZBEE_ZCL_INVALID_STR_LENGTH ) frame_len = 0 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_part_frame_len , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_part_frame , tvb , * offset , frame_len , ENC_NA ) ;
 * offset += frame_len ;
 }