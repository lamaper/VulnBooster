static int dissect_s_supervisor_output_connection_point_owners ( packet_info * pinfo , proto_tree * tree , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 guint16 i , num_entries ;
 proto_item * entry_item , * app_path_item ;
 proto_tree * entry_tree , * epath_tree ;
 int attr_len = 0 , app_path_size ;
 if ( total_len < 2 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_cp_owners ) ;
 return total_len ;
 }
 entry_item = proto_tree_add_item ( tree , hf_cip_ssupervisor_cp_owners_num_entries , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 num_entries = tvb_get_letohs ( tvb , offset ) ;
 attr_len += 2 ;
 if ( num_entries > 0 ) {
 entry_tree = proto_item_add_subtree ( entry_item , ett_ssupervisor_output_cp_owners ) ;
 for ( i = 0 ;
 i < num_entries ;
 i ++ ) {
 if ( total_len < attr_len + 11 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_cp_owners_entry ) ;
 return total_len ;
 }
 dissect_unid ( tvb , pinfo , offset + attr_len , entry_item , "OCPUNID SSN" , hf_cip_ssupervisor_output_cp_owners_ocpunid_ssn_timestamp , hf_cip_ssupervisor_output_cp_owners_ocpunid_ssn_date , hf_cip_ssupervisor_output_cp_owners_ocpunid_ssn_time , hf_cip_ssupervisor_output_cp_owners_ocpunid_macid , ett_ssupervisor_output_cp_owners_ocpunid , ett_ssupervisor_output_cp_owners_ocpunid_ssn ) ;
 attr_len += 10 ;
 proto_tree_add_item ( entry_tree , hf_cip_ssupervisor_cp_owners_app_path_size , tvb , offset + attr_len , 1 , ENC_LITTLE_ENDIAN ) ;
 app_path_size = tvb_get_guint8 ( tvb , offset + attr_len ) ;
 attr_len += 1 ;
 if ( total_len < attr_len + app_path_size ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_cp_owners_app_path_size ) ;
 return total_len ;
 }
 epath_tree = proto_tree_add_subtree ( entry_tree , tvb , offset + attr_len , app_path_size , ett_path , & app_path_item , "Application Resource: " ) ;
 dissect_epath ( tvb , pinfo , epath_tree , app_path_item , offset + attr_len , app_path_size , FALSE , TRUE , NULL , NULL , NO_DISPLAY , NULL , FALSE ) ;
 attr_len += app_path_size ;
 }
 }
 return attr_len ;
 }