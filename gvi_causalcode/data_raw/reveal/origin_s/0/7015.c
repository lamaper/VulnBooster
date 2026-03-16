void proto_register_zbee_zcl_ota ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_ota_attr_id , {
 "Attribute" , "zbee_zcl_general.ota.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_ota_attr_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.ota.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_ota_srv_tx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.ota.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_ota_srv_rx_cmd_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_image_upgrade_status , {
 "Image Upgrade Status" , "zbee_zcl_general.ota.status_attr" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_ota_image_upgrade_attr_status_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_zb_stack_ver , {
 "ZigBee Stack Version" , "zbee_zcl_general.ota.zb_stack.ver" , FT_UINT16 , BASE_HEX | BASE_RANGE_STRING , RVALS ( zbee_zcl_ota_zb_stack_ver_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_payload_type , {
 "Payload Type" , "zbee_zcl_general.ota.payload.type" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_ota_paylaod_type_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_query_jitter , {
 "Query Jitter" , "zbee_zcl_general.ota.query_jitter" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_seconds ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_manufacturer_code , {
 "Manufacturer Code" , "zbee_zcl_general.ota.manufacturer_code" , FT_UINT16 , BASE_HEX , VALS ( zbee_mfr_code_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_image_type , {
 "Image Type" , "zbee_zcl_general.ota.image.type" , FT_UINT16 , BASE_HEX | BASE_RANGE_STRING , RVALS ( zbee_zcl_ota_image_type_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_file_version , {
 "File Version" , "zbee_zcl_general.ota.file.version" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_file_version_appl_release , {
 "Application Release" , "zbee_zcl_general.ota.file.version.appl.release" , FT_UINT32 , BASE_DEC , NULL , ZBEE_ZCL_OTA_FILE_VERS_APPL_RELEASE , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_file_version_appl_build , {
 "Application Build" , "zbee_zcl_general.ota.file.version.appl.build" , FT_UINT32 , BASE_DEC , NULL , ZBEE_ZCL_OTA_FILE_VERS_APPL_BUILD , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_file_version_stack_release , {
 "Stack Release" , "zbee_zcl_general.ota.file.version.stack.release" , FT_UINT32 , BASE_DEC , NULL , ZBEE_ZCL_OTA_FILE_VERS_STACK_RELEASE , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_file_version_stack_build , {
 "Stack Build" , "zbee_zcl_general.ota.file.version.stack.build" , FT_UINT32 , BASE_DEC , NULL , ZBEE_ZCL_OTA_FILE_VERS_STACK_BUILD , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_field_ctrl , {
 "Field Control" , "zbee_zcl_general.ota.field_ctrl" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_field_ctrl_hw_ver_present , {
 "Hardware Version" , "zbee_zcl_general.ota.field_ctrl_hw_ver_present" , FT_BOOLEAN , 8 , TFS ( & tfs_present_not_present ) , ZBEE_ZCL_OTA_FIELD_CTRL_HW_VER_PRESENT , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_field_ctrl_reserved , {
 "Reserved" , "zbee_zcl_general.ota.field_ctrl_reserved" , FT_UINT8 , BASE_HEX , NULL , ZBEE_ZCL_OTA_FIELD_CTRL_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_hw_version , {
 "Hardware Version" , "zbee_zcl_general.ota.hw_ver" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_status , {
 "Status" , "zbee_zcl_general.ota.status" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_status_names ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_image_size , {
 "Image Size" , "zbee_zcl_general.ota.image.size" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( decode_zcl_ota_size_in_bytes ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_file_offset , {
 "File Offset" , "zbee_zcl_general.ota.file.offset" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_max_data_size , {
 "Max Data Size" , "zbee_zcl_general.ota.max_data_size" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_req_node_addr , {
 "Ieee Address" , "zbee_zcl_general.ota.ieee_addr" , FT_UINT64 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_page_size , {
 "Page Size" , "zbee_zcl_general.ota.page.size" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_ota_size_in_bytes ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_rsp_spacing , {
 "Response Spacing" , "zbee_zcl_general.ota.rsp_spacing" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_current_time , {
 "Current Time" , "zbee_zcl_general.ota.current_time" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( decode_zcl_ota_curr_time ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_request_time , {
 "Request Time" , "zbee_zcl_general.ota.request_time" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( decode_zcl_ota_req_time ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_upgrade_time , {
 "Upgrade Time" , "zbee_zcl_general.ota.upgrade_time" , FT_UINT32 , BASE_CUSTOM , CF_FUNC ( decode_zcl_ota_upgr_time ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_data_size , {
 "Data Size" , "zbee_zcl_general.ota.data_size" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ota_image_data , {
 "Image Data" , "zbee_zcl_general.ota.image.data" , FT_BYTES , SEP_COLON , NULL , 0x00 , NULL , HFILL }
 }
 }
 ;
 gint * ett [ ZBEE_ZCL_OTA_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_ota ;
 ett [ 1 ] = & ett_zbee_zcl_ota_field_ctrl ;
 ett [ 2 ] = & ett_zbee_zcl_ota_file_version ;
 proto_zbee_zcl_ota = proto_register_protocol ( "ZigBee ZCL OTA" , "ZCL OTA" , ZBEE_PROTOABBREV_ZCL_OTA ) ;
 proto_register_field_array ( proto_zbee_zcl_ota , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_OTA , dissect_zbee_zcl_ota , proto_zbee_zcl_ota ) ;
 }