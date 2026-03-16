static void dissect_zcl_pwr_prof_pwrprofnotif ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree * sub_tree = NULL ;
 guint i ;
 guint8 total_profile_number ;
 guint8 num_of_transferred_phases ;
 total_profile_number = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_tot_prof_num , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 if ( total_profile_number != 0 ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_pwr_prof_id , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 num_of_transferred_phases = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_num_of_trans_phases , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 for ( i = 0 ;
 i < num_of_transferred_phases ;
 i ++ ) {
 sub_tree = proto_tree_add_subtree_format ( tree , tvb , * offset , 1 , ett_zbee_zcl_pwr_prof_enphases [ i ] , NULL , "Energy Phase #%u" , i ) ;
 dissect_zcl_energy_phase ( tvb , sub_tree , offset ) ;
 }
 }
 }