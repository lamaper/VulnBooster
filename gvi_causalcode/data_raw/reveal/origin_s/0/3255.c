static void dissect_zcl_pwr_prof_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 static const int * format_fields [ ] = {
 & hf_zbee_zcl_pwr_prof_energy_format_rdigit , & hf_zbee_zcl_pwr_prof_energy_format_ldigit , & hf_zbee_zcl_pwr_prof_energy_format_noleadingzero , NULL }
 ;
 static const int * modes [ ] = {
 & hf_zbee_zcl_pwr_prof_sched_mode_cheapest , & hf_zbee_zcl_pwr_prof_sched_mode_greenest , & hf_zbee_zcl_pwr_prof_sched_mode_reserved , NULL }
 ;
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_PWR_PROF_TOT_PROF_NUM : proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_tot_prof_num , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_PWR_PROF_MULTIPLE_SCHED : proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_multiple_sched , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_PWR_PROF_ENERGY_FORMAT : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_pwr_prof_energy_format , ett_zbee_zcl_pwr_prof_en_format , format_fields , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_PWR_PROF_ENERGY_REMOTE : proto_tree_add_item ( tree , hf_zbee_zcl_pwr_prof_energy_remote , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_PWR_PROF_SCHED_MODE : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_pwr_prof_sched_mode , ett_zbee_zcl_pwr_prof_sched_mode , modes , ENC_NA ) ;
 * offset += 1 ;
 break ;
 default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }