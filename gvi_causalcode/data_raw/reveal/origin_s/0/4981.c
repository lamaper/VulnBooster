static void dissect_zcl_sched_energy_phase ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_energy_phase_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_scheduled_time , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }