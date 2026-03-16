static int dissect_s_supervisor_proposed_tunid ( packet_info * pinfo , proto_tree * tree _U_ , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 if ( total_len < 10 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_proposed_tunid ) ;
 return total_len ;
 }
 dissect_unid ( tvb , pinfo , offset , item , "Proposed TUNID SSN" , hf_cip_ssupervisor_proposed_tunid_ssn_timestamp , hf_cip_ssupervisor_proposed_tunid_ssn_date , hf_cip_ssupervisor_proposed_tunid_ssn_time , hf_cip_ssupervisor_proposed_tunid_macid , ett_ssupervisor_proposed_tunid , ett_ssupervisor_proposed_tunid_ssn ) ;
 return 10 ;
 }