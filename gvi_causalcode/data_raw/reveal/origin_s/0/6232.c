static void dissect_zcl_appl_ctrl_signal_state_rsp ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 static const int * flags [ ] = {
 & hf_zbee_zcl_appl_ctrl_rem_en_flags , & hf_zbee_zcl_appl_ctrl_status2 , NULL }
 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_ctrl_appl_status , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_appl_ctrl_rem_en_flags_raw , ett_zbee_zcl_appl_ctrl_flags , flags , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_ctrl_status2_array , tvb , * offset , 3 , ENC_BIG_ENDIAN ) ;
 }