static int dissect_s_supervisor_exception_detail_warning ( packet_info * pinfo , proto_tree * tree , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 proto_item * pi ;
 proto_tree * item_tree ;
 int total_size = 0 , size ;
 item_tree = proto_tree_add_subtree ( tree , tvb , offset , 1 , ett_exception_detail_warning_common , & pi , "Common Exception Detail" ) ;
 size = dissect_s_supervisor_exception_detail ( item_tree , pi , tvb , offset , hf_cip_ssupervisor_exception_detail_warning_ced_size , hf_cip_ssupervisor_exception_detail_warning_ced_detail ) ;
 if ( size == 0 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_detail_warning_ced ) ;
 return total_len ;
 }
 total_size += size ;
 item_tree = proto_tree_add_subtree ( tree , tvb , offset , 1 , ett_exception_detail_warning_device , & pi , "Device Exception Detail" ) ;
 size = dissect_s_supervisor_exception_detail ( item_tree , pi , tvb , offset , hf_cip_ssupervisor_exception_detail_warning_ded_size , hf_cip_ssupervisor_exception_detail_warning_ded_detail ) ;
 if ( size == 0 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_detail_warning_ded ) ;
 return total_len ;
 }
 total_size += size ;
 item_tree = proto_tree_add_subtree ( tree , tvb , offset , 1 , ett_exception_detail_warning_manufacturer , & pi , "Manufacturer Exception Detail" ) ;
 size = dissect_s_supervisor_exception_detail ( item_tree , pi , tvb , offset , hf_cip_ssupervisor_exception_detail_warning_med_size , hf_cip_ssupervisor_exception_detail_warning_med_detail ) ;
 if ( size == 0 ) {
 expert_add_info ( pinfo , item , & ei_mal_ssupervisor_detail_warning_med ) ;
 return total_len ;
 }
 total_size += size ;
 return total_size ;
 }