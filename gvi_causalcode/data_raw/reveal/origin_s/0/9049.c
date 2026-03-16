static void dissect_zcl_pwr_prof_pwrprofschedcontrsnotif ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_start_after , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_stop_before , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }