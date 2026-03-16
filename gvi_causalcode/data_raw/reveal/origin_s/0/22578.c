static void dissect_cip_s_supervisor_data ( proto_tree * item_tree , tvbuff_t * tvb , int offset , int item_length , packet_info * pinfo ) {
 proto_item * pi , * rrsc_item ;
 proto_tree * rrsc_tree , * cmd_data_tree , * bitmap_tree ;
 int req_path_size ;
 int temp_data ;
 guint8 service , gen_status , add_stat_size ;
 cip_req_info_t * preq_info ;
 cip_simple_request_info_t req_data ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "CIPS Supervisor" ) ;
 service = tvb_get_guint8 ( tvb , offset ) ;
 rrsc_tree = proto_tree_add_subtree ( item_tree , tvb , offset , 1 , ett_ssupervisor_rrsc , & rrsc_item , "Service: " ) ;
 proto_tree_add_item ( rrsc_tree , hf_cip_reqrsp , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_item_append_text ( rrsc_item , "%s (%s)" , val_to_str ( ( service & 0x7F ) , cip_sc_vals_ssupervisor , "Unknown Service (0x%02x)" ) , val_to_str_const ( ( service & 0x80 ) >> 7 , cip_sc_rr , "" ) ) ;
 proto_tree_add_item ( rrsc_tree , hf_cip_ssupervisor_sc , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 preq_info = ( cip_req_info_t * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_cip , 0 ) ;
 if ( ( preq_info != NULL ) && ( preq_info -> ciaData != NULL ) ) {
 memcpy ( & req_data , preq_info -> ciaData , sizeof ( cip_simple_request_info_t ) ) ;
 }
 else {
 req_data . iClass = ( guint32 ) - 1 ;
 req_data . iInstance = ( guint32 ) - 1 ;
 req_data . iAttribute = ( guint32 ) - 1 ;
 req_data . iMember = ( guint32 ) - 1 ;
 }
 if ( service & 0x80 ) {
 gen_status = tvb_get_guint8 ( tvb , offset + 2 ) ;
 add_stat_size = tvb_get_guint8 ( tvb , offset + 3 ) * 2 ;
 if ( ( item_length - 4 - add_stat_size ) != 0 ) {
 cmd_data_tree = proto_tree_add_subtree ( item_tree , tvb , offset + 4 + add_stat_size , item_length - 4 - add_stat_size , ett_ssupervisor_cmd_data , NULL , "Command Specific Data" ) ;
 if ( gen_status == CI_GRC_SUCCESS || gen_status == CI_GRC_SERVICE_ERROR ) {
 switch ( service & 0x7F ) {
 case SC_SSUPER_VALIDATE_CONFIGURATION : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_validate_configuration_sccrc , tvb , offset + 4 + add_stat_size , 4 , ENC_LITTLE_ENDIAN ) ;
 dissect_cipsafety_ssn ( cmd_data_tree , tvb , pinfo , offset + 4 + add_stat_size + 4 , hf_cip_ssupervisor_validate_configuration_scts_timestamp , hf_cip_ssupervisor_validate_configuration_scts_date , hf_cip_ssupervisor_validate_configuration_scts_time ) ;
 break ;
 }
 }
 else if ( ( gen_status == 0xD0 ) && ( ( service & 0x7F ) == SC_SSUPER_VALIDATE_CONFIGURATION ) ) {
 if ( add_stat_size > 0 ) {
 proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_validate_configuration_ext_error , tvb , offset + 4 , 2 , ENC_LITTLE_ENDIAN ) ;
 }
 }
 else {
 proto_tree_add_item ( cmd_data_tree , hf_cip_data , tvb , offset + 4 + add_stat_size , item_length - 4 - add_stat_size , ENC_NA ) ;
 }
 }
 }
 else {
 req_path_size = tvb_get_guint8 ( tvb , offset + 1 ) * 2 ;
 if ( ( item_length - req_path_size - 2 ) != 0 ) {
 cmd_data_tree = proto_tree_add_subtree ( item_tree , tvb , offset + 2 + req_path_size , item_length - req_path_size - 2 , ett_ssupervisor_cmd_data , NULL , "Command Specific Data" ) ;
 switch ( service ) {
 case SC_SSUPER_RECOVER : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_recover_data , tvb , offset + 2 + req_path_size , item_length - req_path_size - 2 , ENC_NA ) ;
 break ;
 case SC_SSUPER_PERFORM_DIAGNOSTICS : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_perform_diag_data , tvb , offset + 2 + req_path_size , item_length - req_path_size - 2 , ENC_NA ) ;
 break ;
 case SC_SSUPER_CONFIGURE_REQUEST : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_configure_request_password , tvb , offset + 2 + req_path_size , 16 , ENC_NA ) ;
 pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_configure_request_tunid , tvb , offset + 2 + req_path_size + 16 , 10 , ENC_NA ) ;
 dissect_unid ( tvb , pinfo , offset + 2 + req_path_size + 16 , pi , "TUNID SSN" , hf_cip_ssupervisor_configure_request_tunid_ssn_timestamp , hf_cip_ssupervisor_configure_request_tunid_ssn_date , hf_cip_ssupervisor_configure_request_tunid_ssn_time , hf_cip_ssupervisor_configure_request_tunid_macid , ett_ssupervisor_configure_request_tunid , ett_ssupervisor_configure_request_tunid_ssn ) ;
 pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_configure_request_ounid , tvb , offset + 2 + req_path_size + 26 , 10 , ENC_NA ) ;
 dissect_unid ( tvb , pinfo , offset + 2 + req_path_size + 16 , pi , "OUNID SSN" , hf_cip_ssupervisor_configure_request_ounid_ssn_timestamp , hf_cip_ssupervisor_configure_request_ounid_ssn_date , hf_cip_ssupervisor_configure_request_ounid_ssn_time , hf_cip_ssupervisor_configure_request_ounid_macid , ett_ssupervisor_configure_request_ounid , ett_ssupervisor_configure_request_ounid_ssn ) ;
 break ;
 case SC_SSUPER_VALIDATE_CONFIGURATION : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_validate_configuration_sccrc , tvb , offset + 2 + req_path_size , 4 , ENC_LITTLE_ENDIAN ) ;
 dissect_cipsafety_ssn ( cmd_data_tree , tvb , pinfo , offset + 2 + req_path_size + 4 , hf_cip_ssupervisor_validate_configuration_scts_timestamp , hf_cip_ssupervisor_validate_configuration_scts_date , hf_cip_ssupervisor_validate_configuration_scts_time ) ;
 break ;
 case SC_SSUPER_SET_PASSWORD : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_set_password_current_password , tvb , offset + 2 + req_path_size , 16 , ENC_NA ) ;
 proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_set_password_new_password , tvb , offset + 2 + req_path_size + 16 , 16 , ENC_NA ) ;
 break ;
 case SC_SSUPER_CONFIGURATION_LOCK : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_configure_lock_value , tvb , offset + 2 + req_path_size + 1 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_configure_lock_password , tvb , offset + 2 + req_path_size + 1 , 16 , ENC_NA ) ;
 pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_configure_lock_tunid , tvb , offset + 2 + req_path_size + 17 , 10 , ENC_NA ) ;
 dissect_unid ( tvb , pinfo , offset + 2 + req_path_size + 17 , pi , "TUNID SSN" , hf_cip_ssupervisor_configure_lock_tunid_ssn_timestamp , hf_cip_ssupervisor_configure_lock_tunid_ssn_date , hf_cip_ssupervisor_configure_lock_tunid_ssn_time , hf_cip_ssupervisor_configure_lock_tunid_macid , ett_ssupervisor_configure_lock_tunid , ett_ssupervisor_configure_lock_tunid_ssn ) ;
 break ;
 case SC_SSUPER_MODE_CHANGE : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_mode_change_value , tvb , offset + 2 + req_path_size + 1 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_mode_change_password , tvb , offset + 2 + req_path_size + 1 , 16 , ENC_NA ) ;
 break ;
 case SC_SSUPER_SAFETY_RESET : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_reset_type , tvb , offset + 2 + req_path_size + 1 , 1 , ENC_LITTLE_ENDIAN ) ;
 temp_data = tvb_get_guint8 ( tvb , offset + 2 + req_path_size + 1 ) ;
 proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_reset_password , tvb , offset + 2 + req_path_size + 1 , 16 , ENC_NA ) ;
 pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_reset_tunid , tvb , offset + 2 + req_path_size + 17 , 10 , ENC_NA ) ;
 dissect_unid ( tvb , pinfo , offset + 2 + req_path_size + 17 , pi , "TUNID SSN" , hf_cip_ssupervisor_reset_tunid_tunid_ssn_timestamp , hf_cip_ssupervisor_reset_tunid_tunid_ssn_date , hf_cip_ssupervisor_reset_tunid_tunid_ssn_time , hf_cip_ssupervisor_reset_tunid_macid , ett_ssupervisor_reset_tunid , ett_ssupervisor_reset_tunid_ssn ) ;
 if ( temp_data == 2 ) {
 pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_reset_attr_bitmap , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 bitmap_tree = proto_item_add_subtree ( pi , ett_cip_ssupervisor_reset_attr_bitmap ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_macid , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_baudrate , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_tunid , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_password , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_cfunid , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_ocpunid , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_reserved , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( bitmap_tree , hf_cip_ssupervisor_reset_attr_bitmap_extended , tvb , offset + 2 + req_path_size + 27 , 1 , ENC_LITTLE_ENDIAN ) ;
 }
 break ;
 case SC_SSUPER_RESET_PASSWORD : proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_reset_password_data_size , tvb , offset + 2 + req_path_size , 1 , ENC_LITTLE_ENDIAN ) ;
 temp_data = tvb_get_guint8 ( tvb , offset + 2 + req_path_size ) ;
 proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_reset_password_data , tvb , offset + 2 + req_path_size + 1 , temp_data , ENC_NA ) ;
 break ;
 case SC_SSUPER_PROPOSE_TUNID : pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_propose_tunid_tunid , tvb , offset + 2 + req_path_size , 10 , ENC_NA ) ;
 dissect_unid ( tvb , pinfo , offset + 2 + req_path_size , pi , "TUNID SSN" , hf_cip_ssupervisor_propose_tunid_tunid_ssn_timestamp , hf_cip_ssupervisor_propose_tunid_tunid_ssn_date , hf_cip_ssupervisor_propose_tunid_tunid_ssn_time , hf_cip_ssupervisor_propose_tunid_tunid_macid , ett_ssupervisor_propose_tunid , ett_ssupervisor_propose_tunid_ssn ) ;
 break ;
 case SC_SSUPER_APPLY_TUNID : pi = proto_tree_add_item ( cmd_data_tree , hf_cip_ssupervisor_apply_tunid_tunid , tvb , offset + 2 + req_path_size , 10 , ENC_NA ) ;
 dissect_unid ( tvb , pinfo , offset + 2 + req_path_size , pi , "TUNID SSN" , hf_cip_ssupervisor_apply_tunid_tunid_ssn_timestamp , hf_cip_ssupervisor_apply_tunid_tunid_ssn_date , hf_cip_ssupervisor_apply_tunid_tunid_ssn_time , hf_cip_ssupervisor_apply_tunid_tunid_macid , ett_ssupervisor_apply_tunid , ett_ssupervisor_apply_tunid_ssn ) ;
 break ;
 default : proto_tree_add_item ( cmd_data_tree , hf_cip_data , tvb , offset + 2 + req_path_size , item_length - req_path_size - 2 , ENC_NA ) ;
 }
 }
 }
 add_cip_service_to_info_column ( pinfo , service , cip_sc_vals_ssupervisor ) ;
 }