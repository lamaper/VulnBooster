static void dissect_cip_s_validator_data ( proto_tree * item_tree , tvbuff_t * tvb , int offset , int item_length , packet_info * pinfo ) {
 proto_item * pi , * rrsc_item ;
 proto_tree * rrsc_tree , * cmd_data_tree ;
 int req_path_size ;
 guint8 service , gen_status , add_stat_size ;
 cip_req_info_t * preq_info ;
 cip_simple_request_info_t req_data ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "CIPS Validator" ) ;
 service = tvb_get_guint8 ( tvb , offset ) ;
 rrsc_tree = proto_tree_add_subtree ( item_tree , tvb , offset , 1 , ett_svalidator_rrsc , & rrsc_item , "Service: " ) ;
 proto_tree_add_item ( rrsc_tree , hf_cip_reqrsp , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_item_append_text ( rrsc_item , "%s (%s)" , val_to_str ( ( service & 0x7F ) , cip_sc_vals_svalidator , "Unknown Service (0x%02x)" ) , val_to_str_const ( ( service & 0x80 ) >> 7 , cip_sc_rr , "" ) ) ;
 proto_tree_add_item ( rrsc_tree , hf_cip_svalidator_sc , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
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
 cmd_data_tree = proto_tree_add_subtree ( item_tree , tvb , offset + 4 + add_stat_size , item_length - 4 - add_stat_size , ett_ssupervisor_cmd_data , & pi , "Command Specific Data" ) ;
 if ( gen_status == CI_GRC_SUCCESS || gen_status == CI_GRC_SERVICE_ERROR ) {
 if ( ( ( service & 0x7F ) == SC_GET_ATT_ALL ) && ( req_data . iInstance != ( guint32 ) - 1 ) && ( req_data . iInstance != 0 ) ) {
 dissect_cip_get_attribute_all_rsp ( tvb , pinfo , cmd_data_tree , offset + 4 + add_stat_size , & req_data ) ;
 }
 else {
 proto_tree_add_item ( cmd_data_tree , hf_cip_data , tvb , offset + 4 + add_stat_size , item_length - 4 - add_stat_size , ENC_NA ) ;
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
 proto_tree_add_item ( cmd_data_tree , hf_cip_data , tvb , offset + 2 + req_path_size , item_length - req_path_size - 2 , ENC_NA ) ;
 }
 }
 add_cip_service_to_info_column ( pinfo , service , cip_sc_vals_svalidator ) ;
 }