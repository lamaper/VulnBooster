static void dissect_zcl_pwr_prof_pwrprofpriceext ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 static const int * options [ ] = {
 & hf_zbee_zcl_pwr_prof_options_01 , & hf_zbee_zcl_pwr_prof_options_res , NULL }
 ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_pwr_prof_options , ett_zbee_zcl_pwr_prof_options , options , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_stime , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 }