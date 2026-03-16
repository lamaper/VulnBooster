static void dissect_zcl_power_profile ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_energy_phase_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_rem_ctrl , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_state , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 }