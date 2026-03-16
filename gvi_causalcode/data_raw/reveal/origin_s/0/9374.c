static int dissect_s_supervisor_configuration_unid ( packet_info * pinfo , proto_tree * tree _U_ , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 if ( total_len < 10 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_configuration_unid ) ;
 return total_len ;
 }
 dissect_unid ( tvb , pinfo , offset , item , "CFUNID SSN" , hf_cip_ssupervisor_configuration_unid_ssn_timestamp , hf_cip_ssupervisor_configuration_unid_ssn_date , hf_cip_ssupervisor_configuration_unid_ssn_time , hf_cip_ssupervisor_configuration_unid_macid , ett_ssupervisor_configuration_unid , ett_ssupervisor_configuration_unid_ssn ) ;
 return 10 ;
 }