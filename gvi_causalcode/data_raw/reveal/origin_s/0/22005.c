void proto_register_btatt ( void ) {
 module_t * module ;
 expert_module_t * expert_btatt ;
 static hf_register_info hf [ ] = {
 {
 & hf_btatt_opcode , {
 "Opcode" , "btatt.opcode" , FT_UINT8 , BASE_HEX , VALS ( opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_opcode_authentication_signature , {
 "Authentication Signature" , "btatt.opcode.authentication_signature" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_opcode_command , {
 "Command" , "btatt.opcode.command" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_opcode_method , {
 "Method" , "btatt.opcode.method" , FT_UINT8 , BASE_HEX , VALS ( opcode_vals ) , 0x3F , NULL , HFILL }
 }
 , {
 & hf_btatt_handles_info , {
 "Handles Info" , "btatt.handles_info" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_attribute_data , {
 "Attribute Data" , "btatt.attribute_data" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_handle , {
 "Handle" , "btatt.handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_starting_handle , {
 "Starting Handle" , "btatt.starting_handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ending_handle , {
 "Ending Handle" , "btatt.ending_handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_group_end_handle , {
 "Group End Handle" , "btatt.group_end_handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_value , {
 "Value" , "btatt.value" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_req_opcode_in_error , {
 "Request Opcode in Error" , "btatt.req_opcode_in_error" , FT_UINT8 , BASE_HEX , VALS ( opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_handle_in_error , {
 "Handle in Error" , "btatt.handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_aios , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_aios_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_ans , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_ans_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_bms , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_bms_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_cgms , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_cgms_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_cps , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_cps_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_cscs , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_cscs_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_cts , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_cts_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_ess , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_ess_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_gls , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_gls_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_hps , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_hps_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_hrs , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_hrs_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_hts , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_hts_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_ips , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_ips_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_ots , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_ots_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_rscs , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_rscs_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_error_code_uds , {
 "Error Code" , "btatt.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_uds_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_service_uuid16 , {
 "Service UUID" , "btatt.service_uuid16" , FT_UINT16 , BASE_HEX | BASE_EXT_STRING , & bluetooth_uuid_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_service_uuid128 , {
 "Service UUID" , "btatt.service_uuid128" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_uuid16 , {
 "Characteristic UUID" , "btatt.characteristic_uuid16" , FT_UINT16 , BASE_HEX | BASE_EXT_STRING , & bluetooth_uuid_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_uuid128 , {
 "Characteristic UUID" , "btatt.characteristic_uuid128" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uuid16 , {
 "UUID" , "btatt.uuid16" , FT_UINT16 , BASE_HEX | BASE_EXT_STRING , & bluetooth_uuid_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uuid128 , {
 "UUID" , "btatt.uuid128" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_client_rx_mtu , {
 "Client Rx MTU" , "btatt.client_rx_mtu" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_server_rx_mtu , {
 "Server Rx MTU" , "btatt.server_rx_mtu" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uuid_format , {
 "UUID Format" , "btatt.uuid_format" , FT_UINT8 , BASE_HEX , VALS ( uuid_format_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_length , {
 "Length" , "btatt.length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "Length of Handle/Value Pair" , HFILL }
 }
 , {
 & hf_btatt_offset , {
 "Offset" , "btatt.offset" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_flags , {
 "Flags" , "btatt.flags" , FT_UINT8 , BASE_HEX , VALS ( flags_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_sign_counter , {
 "Sign Counter" , "btatt.sign_counter" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_signature , {
 "Signature" , "btatt.signature" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties , {
 "Characteristic Properties" , "btatt.characteristic_properties" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_extended_properties , {
 "Extended Properties" , "btatt.characteristic_properties.extended_properties" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_authenticated_signed_writes , {
 "Authenticated Signed Writes" , "btatt.characteristic_properties.authenticated_signed_writes" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_indicate , {
 "Indicate" , "btatt.characteristic_properties.indicate" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_notify , {
 "Notify" , "btatt.characteristic_properties.notify" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_write , {
 "Write" , "btatt.characteristic_properties.write" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_write_without_response , {
 "Write without Response" , "btatt.characteristic_properties.write_without_response" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_read , {
 "Read" , "btatt.characteristic_properties.read" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_properties_broadcast , {
 "Broadcast" , "btatt.characteristic_properties.broadcast" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_value_handle , {
 "Characteristic Value Handle" , "btatt.handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_included_service_handle , {
 "Included Service Handle" , "btatt.handle" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_information_data , {
 "Information Data" , "btatt.information_data" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_client , {
 "Characteristic Configuration Client" , "btatt.characteristic_configuration_client" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_client_reserved , {
 "Reseved" , "btatt.characteristic_configuration_client.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFFFC , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_client_indication , {
 "Indication" , "btatt.characteristic_configuration_client.indication" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_client_notification , {
 "Notification" , "btatt.characteristic_configuration_client.notification" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_server , {
 "Characteristic Configuration Server" , "btatt.characteristic_configuration_server" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_server_reserved , {
 "Reseved" , "btatt.characteristic_configuration_server.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFFFE , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_configuration_server_broadcast , {
 "Broadcast" , "btatt.characteristic_configuration_server.broadcast" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_protocol_mode , {
 "Protocol Mode" , "btatt.hogp.protocol_mode" , FT_UINT8 , BASE_HEX , VALS ( hogp_protocol_mode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_report_reference_report_id , {
 "Report ID" , "btatt.report_reference.report_id" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_report_reference_report_type , {
 "Report Type" , "btatt.report_reference.report_id" , FT_UINT8 , BASE_HEX , VALS ( report_reference_report_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_bcd_hid , {
 "bcdHID" , "btatt.hogp.bcd_hid" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_b_country_code , {
 "bCountryCode" , "btatt.hogp.b_country_code" , FT_UINT8 , BASE_HEX , VALS ( hid_country_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_flags , {
 "Flags" , "btatt.hogp.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_flags_reserved , {
 "Reserved" , "btatt.hogp.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xFC , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_flags_normally_connectable , {
 "Normally Connectable" , "btatt.hogp.flags.normally_connectable" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_flags_remote_wake , {
 "Remote Wake" , "btatt.hogp.flags.remote_wake" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_user_description , {
 "Characteristic User Description" , "btatt.characteristic_user_description" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_extended_properties , {
 "Characteristic Extended Properties" , "btatt.characteristic_extended_properties" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_extended_properties_reserved , {
 "Reserved" , "btatt.characteristic_extended_properties.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFFFC , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_extended_properties_writable_auxiliaries , {
 "Writable Auxiliaries" , "btatt.characteristic_extended_properties.writable_auxiliaries" , FT_UINT16 , BASE_HEX , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_extended_properties_reliable_write , {
 "Reliable Write" , "btatt.characteristic_extended_properties.reliable_write" , FT_UINT16 , BASE_HEX , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_presentation_format , {
 "Format" , "btatt.characteristic_presentation.format" , FT_UINT8 , BASE_HEX , VALS ( characteristic_presentation_format_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_presentation_exponent , {
 "Exponent" , "btatt.characteristic_presentation.exponent" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_presentation_unit , {
 "Unit" , "btatt.characteristic_presentation.unit" , FT_UINT16 , BASE_HEX | BASE_EXT_STRING , & bluetooth_uuid_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_presentation_namespace , {
 "Namespace" , "btatt.characteristic_presentation.namespace" , FT_UINT8 , BASE_HEX , VALS ( characteristic_presentation_namespace_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_presentation_namespace_description , {
 "Namespace Description" , "btatt.characteristic_presentation.namespace_description" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_characteristic_presentation_namespace_description_btsig , {
 "Namespace Description" , "btatt.characteristic_presentation.namespace_description" , FT_UINT16 , BASE_HEX , VALS ( characteristic_presentation_namespace_description_btsig_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_trigger_logic , {
 "Trigger Logic" , "btatt.esp.trigger_logic" , FT_UINT8 , BASE_HEX , VALS ( esp_trigger_logic_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_condition , {
 "Trigger Logic" , "btatt.esp.condition" , FT_UINT8 , BASE_HEX , VALS ( esp_condition_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_operand , {
 "Operand" , "btatt.esp.operand" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_flags , {
 "Flags" , "btatt.esp.flags" , FT_UINT16 , BASE_HEX , NULL , 0xFFFF , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_sampling_function , {
 "Sampling Function" , "btatt.esp.sampling_function" , FT_UINT8 , BASE_HEX , VALS ( esp_sampling_function_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_measurement_period , {
 "Measurement Period" , "btatt.esp.measurement_period" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_update_interval , {
 "Update Interval" , "btatt.esp.update_interval" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_application , {
 "Application" , "btatt.esp.application" , FT_UINT8 , BASE_HEX , VALS ( esp_application_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_esp_measurement_uncertainty , {
 "Measurement Uncertainty" , "btatt.esp.measurement_uncertainty" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_device_name , {
 "Device Name" , "btatt.device_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance , {
 "Appearance" , "btatt.appearance" , FT_UINT16 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_category , {
 "Category" , "btatt.appearance.category" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_category_vals ) , 0xFFC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory , {
 "Subcategory" , "btatt.appearance.subcategory" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_generic_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_watch , {
 "Subcategory" , "btatt.appearance.subcategory.watch" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_watch_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_thermometer , {
 "Subcategory" , "btatt.appearance.subcategory.thermometer" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_thermometer_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_heart_rate , {
 "Subcategory" , "btatt.appearance.subcategory.heart_rate" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_heart_rate_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_blood_pressure , {
 "Subcategory" , "btatt.appearance.subcategory.blood_pressure" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_blood_pressure_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_hid , {
 "Subcategory" , "btatt.appearance.subcategory.hid" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_hid_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_running_walking_sensor , {
 "Subcategory" , "btatt.appearance.subcategory.running_walking_sensor" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_running_walking_sensor_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_cycling , {
 "Subcategory" , "btatt.appearance.subcategory.cycling" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_cycling_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_pulse_oximeter , {
 "Subcategory" , "btatt.appearance.subcategory.pulse_oximeter" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_pulse_oximeter_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_personal_mobility_device , {
 "Personal Mobility Device" , "btatt.appearance.subcategory.personal_mobility_device" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_personal_mobility_device_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_insulin_pump , {
 "Insulin Pump" , "btatt.appearance.subcategory.insulin_pump" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_insulin_pump_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_appearance_subcategory_outdoor_sports_activity , {
 "Subcategory" , "btatt.appearance.subcategory.outdoor_sports_activity" , FT_UINT16 , BASE_DEC_HEX , VALS ( appearance_subcategory_outdoor_sports_activity_vals ) , 0x003F , NULL , HFILL }
 }
 , {
 & hf_btatt_peripheral_privacy_flag , {
 "Peripheral Privacy" , "btatt.peripheral_privacy_flag" , FT_BOOLEAN , 8 , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_reconnection_address , {
 "Reconnection Address" , "btatt.reconnection_address" , FT_ETHER , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_minimum_connection_interval , {
 "Minimum Connection Interval" , "btatt.minimum_connection_interval" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_maximum_connection_interval , {
 "Maximum Connection Interval" , "btatt.maximum_connection_interval" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_slave_latency , {
 "Slave Latency" , "btatt.slave_latency" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_connection_supervision_timeout_multiplier , {
 "Connection Supervision Timeout Multiplier" , "btatt.connection_supervision_timeout_multiplier" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_level , {
 "Alert Level" , "btatt.alert_level" , FT_UINT8 , BASE_HEX , VALS ( alert_level_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_tx_power_level , {
 "Tx Power Level" , "btatt.tx_power_level" , FT_INT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_year , {
 "Year" , "btatt.year" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_month , {
 "Month" , "btatt.month" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_day , {
 "Day" , "btatt.day" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hours , {
 "Hours" , "btatt.hours" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_minutes , {
 "Minutes" , "btatt.minutes" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_seconds , {
 "Seconds" , "btatt.seconds" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_day_of_week , {
 "Day of Week" , "btatt.day_of_week" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_fractions100 , {
 "Fractions100" , "btatt.fractions100" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "1/100th of a second" , HFILL }
 }
 , {
 & hf_btatt_fractions256 , {
 "Fractions256" , "btatt.fractions256" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "1/256th of a second" , HFILL }
 }
 , {
 & hf_btatt_dst_offset , {
 "Daylight Saving Time Offset" , "btatt.dst_offset" , FT_UINT8 , BASE_HEX , VALS ( dst_offset_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_model_number_string , {
 "Model Number String" , "btatt.model_number_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_serial_number_string , {
 "Serial Number String" , "btatt.serial_number_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_firmware_revision_string , {
 "Firmware Revision String" , "btatt.firmware_revision_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hardware_revision_string , {
 "Hardware Revision String" , "btatt.hardware_revision_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_software_revision_string , {
 "Software Revision String" , "btatt.software_revision_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_manufacturer_string , {
 "Manufacturer String" , "btatt.manufacturer_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_system_id_manufacturer_identifier , {
 "Manufacturer Identifier" , "btatt.system_id.manufacturer_identifier" , FT_UINT40 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_system_id_organizationally_unique_identifier , {
 "Organizationally Unique Identifier" , "btatt.system_id.organizationally_unique_identifier" , FT_UINT24 , BASE_OUI , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_timezone , {
 "Timezone" , "btatt.timezone" , FT_INT8 , BASE_DEC , VALS ( timezone_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_accuracy , {
 "Time Accuracy" , "btatt.time_accuracy" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_source , {
 "Time Source" , "btatt.time_source" , FT_UINT8 , BASE_DEC , VALS ( time_source_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_days_since_update , {
 "Days Since Update" , "btatt.days_since_update" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_hours_since_update , {
 "Hours Since Update" , "btatt.hours_since_update" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_update_control_point , {
 "Update Control Point" , "btatt.update_control_point" , FT_UINT8 , BASE_HEX , VALS ( time_update_control_point_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_current_state , {
 "Current State" , "btatt.time_current_state" , FT_UINT8 , BASE_HEX , VALS ( time_current_state_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_result , {
 "Result" , "btatt.time_result" , FT_UINT8 , BASE_HEX , VALS ( time_result_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_battery_level , {
 "Battery Level" , "btatt.battery_level" , FT_UINT8 , BASE_DEC | BASE_UNIT_STRING , & units_percent , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_battery_power_state , {
 "Battery Power State" , "btatt.battery_power_state" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_battery_power_state_level , {
 "Level" , "btatt.battery_power_state.level" , FT_UINT8 , BASE_HEX , VALS ( battery_power_state_level_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_battery_power_state_charging , {
 "Charging" , "btatt.battery_power_state.charging" , FT_UINT8 , BASE_HEX , VALS ( battery_power_state_charging_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_battery_power_state_discharging , {
 "Discharging" , "btatt.battery_power_state.discharging" , FT_UINT8 , BASE_HEX , VALS ( battery_power_state_discharging_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_battery_power_state_present , {
 "Present" , "btatt.battery_power_state.present" , FT_UINT8 , BASE_HEX , VALS ( battery_power_state_present_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_type , {
 "Temperature Type" , "btatt.temperature_type" , FT_UINT8 , BASE_HEX , VALS ( temperature_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_measurement_interval , {
 "Measurement Interval" , "btatt.measurement_interval" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_adjust_reason , {
 "Adjust Reason" , "btatt.adjust_reason" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_adjust_reason_reserved , {
 "Reserved" , "btatt.adjust_reason.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_adjust_reason_change_of_dst , {
 "Change of DST" , "btatt.adjust_reason.change_of_dst" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_adjust_reason_change_of_timezone , {
 "Change of Timezone" , "btatt.adjust_reason.change_of_timezone" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_adjust_reason_external_reference_time_update , {
 "External Reference Time Update" , "btatt.adjust_reason.external_reference_time_update" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_adjust_reason_manual_time_update , {
 "Manual Time Update" , "btatt.adjust_reason.manual_time_update" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_magnetic_declination , {
 "Magnetic Declination" , "btatt.magnetic_declination" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_scan_refresh , {
 "Scan Refresh" , "btatt.scan_refresh" , FT_UINT8 , BASE_HEX , VALS ( scan_refresh_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_sensor_location , {
 "Body Sensor Location" , "btatt.body_sensor_location" , FT_UINT8 , BASE_HEX , VALS ( body_sensor_location_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_control_point , {
 "Heart Rate Control Point" , "btatt.heart_rate_control_point" , FT_UINT8 , BASE_HEX , VALS ( heart_rate_control_point_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_status , {
 "Alert Status" , "btatt.alert.status" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_status_reserved , {
 "Reserved" , "btatt.alert.status.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xF8 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_status_display_alert_status , {
 "Display Alert Status" , "btatt.alert.status.display_alert_status" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_status_vibrate_state , {
 "Vibrate State" , "btatt.alert.status.vibrate_state" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_status_ringer_state , {
 "Ringer State" , "btatt.alert_status.ringer_state" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_ringer_control_point , {
 "Ringer Control Point" , "btatt.ringer_control_point" , FT_UINT8 , BASE_HEX , VALS ( ringer_control_point_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ringer_setting , {
 "Ringer Setting" , "btatt.ringer_setting" , FT_UINT8 , BASE_HEX , VALS ( ringer_setting_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1 , {
 "Alert Category ID Bitmask 1" , "btatt.alert.category_id_bitmask_1" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_schedule , {
 "Schedule" , "btatt.alert.category_id_bitmask_1.schedule" , FT_UINT8 , BASE_HEX , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_voice_mail , {
 "Voice Mail" , "btatt.alert.category_id_bitmask_1.voice_mail" , FT_UINT8 , BASE_HEX , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_sms_mms , {
 "SMS/MMS" , "btatt.alert.category_id_bitmask_1.sms_mms" , FT_UINT8 , BASE_HEX , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_missed_call , {
 "Missed Call" , "btatt.alert.category_id_bitmask_1.missed_call" , FT_UINT8 , BASE_HEX , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_call , {
 "Call" , "btatt.alert.category_id_bitmask_1.call" , FT_UINT8 , BASE_HEX , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_news , {
 "News" , "btatt.alert.category_id_bitmask_1.news" , FT_UINT8 , BASE_HEX , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_email , {
 "Email" , "btatt.alert.category_id_bitmask_1.email" , FT_UINT8 , BASE_HEX , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_1_simple_alert , {
 "Simple Alert" , "btatt.alert.category_id_bitmask_1.simple_alert" , FT_UINT8 , BASE_HEX , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_2 , {
 "Alert Category ID Bitmask 2" , "btatt.alert.category_id_bitmask_2" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_2_reserved , {
 "Reserved" , "btatt.alert.category_id_bitmask_2.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xFC , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_2_instant_message , {
 "Instant Message" , "btatt.alert.category_id_bitmask_2.instant_message" , FT_UINT8 , BASE_HEX , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id_bitmask_2_high_prioritized_alert , {
 "High Prioritized Alert" , "btatt.alert.category_id_bitmask_2.high_prioritized_alert" , FT_UINT8 , BASE_HEX , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_category_id , {
 "Alert Category ID" , "btatt.alert.category_id" , FT_UINT8 , BASE_HEX , VALS ( alert_category_id_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_command_id , {
 "Alert Command ID" , "btatt.alert.command_id" , FT_UINT8 , BASE_HEX , VALS ( alert_command_id_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_unread_count , {
 "Unread Count" , "btatt.alert.unread_count" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_number_of_new_alert , {
 "Number of New Alert" , "btatt.alert.number_of_new_alert" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_alert_text_string_information , {
 "Text String Information" , "btatt.text_string_information" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature , {
 "Blood Pressure Feature" , "btatt.blood_pressure.feature" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_reserved , {
 "Reserved" , "btatt.blood_pressure.feature.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFFC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_multiple_bond , {
 "Multiple Bond" , "btatt.blood_pressure.feature.multiple_bond" , FT_BOOLEAN , 16 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_measurement_position_detection , {
 "Measurement Position Detection" , "btatt.blood_pressure.feature.measurement_position_detection" , FT_BOOLEAN , 16 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_puls_rate_range , {
 "Puls Rate Range" , "btatt.blood_pressure.feature.puls_rate_range" , FT_BOOLEAN , 16 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_irregular_pulse_detection , {
 "Irregular Pulse Detection" , "btatt.blood_pressure.feature.irregular_pulse_detection" , FT_BOOLEAN , 16 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_cuff_fit_detection , {
 "Cuff Fit Detection" , "btatt.blood_pressure.feature.cuff_fit_detection" , FT_BOOLEAN , 16 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_feature_body_movement_detection , {
 "Body Movement Detection" , "btatt.blood_pressure.feature.body_movement_detection" , FT_BOOLEAN , 16 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_hogp_hid_control_point_command , {
 "HID Control Point Command" , "btatt.hogp.hid_control_point_command" , FT_UINT8 , BASE_HEX , VALS ( hid_control_point_command_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_le_scan_interval , {
 "LE Scan Interval" , "btatt.le_scan_interval" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_le_scan_window , {
 "LE Scan Window" , "btatt.le_scan_window" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pnp_id_vendor_id_source , {
 "Vendor ID Source" , "btatt.pnp_id.vendor_id_source" , FT_UINT16 , BASE_HEX , VALS ( pnp_id_vendor_id_source_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pnp_id_vendor_id , {
 "Vendor ID" , "btatt.pnp_id.vendor_id" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pnp_id_vendor_id_bluetooth_sig , {
 "Vendor ID" , "btatt.pnp_id.vendor_id" , FT_UINT16 , BASE_HEX | BASE_EXT_STRING , & bluetooth_company_id_vals_ext , 0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pnp_id_vendor_id_usb_forum , {
 "Vendor ID" , "btatt.pnp_id.vendor_id" , FT_UINT16 , BASE_HEX | BASE_EXT_STRING , & ext_usb_vendors_vals , 0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pnp_id_product_id , {
 "Product ID" , "btatt.pnp_id.product_id" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pnp_id_product_version , {
 "Version" , "btatt.pnp_id.product_version" , FT_UINT16 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature , {
 "Glucose Feature" , "btatt.glucose.feature" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_reserved , {
 "Reserved" , "btatt.glucose.feature.reserved" , FT_BOOLEAN , 16 , NULL , 0xF800 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_multiple_bond , {
 "Multiple Bond" , "btatt.glucose.feature.multiple_bond" , FT_BOOLEAN , 16 , NULL , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_time_fault , {
 "Time Fault" , "btatt.glucose.feature.time_fault" , FT_BOOLEAN , 16 , NULL , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_general_device_fault , {
 "General Device Fault" , "btatt.glucose.feature.general_device_fault" , FT_BOOLEAN , 16 , NULL , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_read_interrupt_detection , {
 "Sensor Read Interrupt Detection" , "btatt.glucose.feature.sensor_read_interrupt_detection" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_temperature_high_low_detection , {
 "Sensor Temperature High-Low Detection" , "btatt.glucose.feature.sensor_temperature_high_low_detection" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_result_high_low_detection , {
 "Sensor Result High-Low Detection" , "btatt.glucose.feature.sensor_result_high_low_detection" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_strip_type_error_detection , {
 "Sensor Strip Type Error Detection" , "btatt.glucose.feature.sensor_strip_type_error_detection" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_strip_insertion_error_detection , {
 "Sensor Strip Insertion Error Detection" , "btatt.glucose.feature.sensor_strip_insertion_error_detection" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_sample_size , {
 "Sensor Sample Size" , "btatt.glucose.feature.sensor_sample_size" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_sensor_malfunction_detection , {
 "Sensor Malfunction Detection" , "btatt.glucose.feature.sensor_malfunction_detection" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_feature_low_battery_detection_during_measurement , {
 "Low Battery Detection During Measurement" , "btatt.glucose.feature.low_battery_detection_during_measurement" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature , {
 "RSC Feature" , "btatt.rsc.feature" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature_reserved , {
 "Reserved" , "btatt.rsc.feature.reserved" , FT_BOOLEAN , 16 , NULL , 0xFF80 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature_multiple_sensor_locations , {
 "Multiple Sensor Locations" , "btatt.rsc.feature.multiple_sensor_locations" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature_calibration_procedure , {
 "Calibration Procedure" , "btatt.rsc.feature.calibration_procedure" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature_walking_or_running_status , {
 "Walking_or Running Status" , "btatt.rsc.feature.walking_or_running_status" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature_total_distance_measurement , {
 "Total Distance Measurement" , "btatt.rsc.feature.total_distance_measurement" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_feature_instantaneous_stride_length_measurement , {
 "Instantaneous Stride Length Measurement" , "btatt.rsc.feature.instantaneous_stride_length_measurement" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_feature , {
 "CSC Feature" , "btatt.csc.feature" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_feature_reserved , {
 "Reserved" , "btatt.csc.feature.reserved" , FT_BOOLEAN , 16 , NULL , 0xFFF8 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_feature_multiple_sensor_locations , {
 "Multiple Sensor Locations" , "btatt.csc.feature.multiple_sensor_locations" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_feature_crank_revolution_data , {
 "Crank Revolution Data" , "btatt.csc.feature.crank_revolution_data" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_feature_wheel_revolution_data , {
 "Wheel Revolution Data" , "btatt.csc.feature.wheel_revolution_data" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_sensor_location , {
 "Sensor Location" , "btatt.sensor_location" , FT_UINT8 , BASE_HEX , VALS ( sensor_location_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_elevation , {
 "Elevation" , "btatt.elevation" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pressure , {
 "Pressure" , "btatt.pressure" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature , {
 "Temperature" , "btatt.temperature" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_humidity , {
 "Humidity" , "btatt.humidity" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_true_wind_speed , {
 "True Wind Speed" , "btatt.true_wind_speed" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_true_wind_direction , {
 "True Wind Direction" , "btatt.true_wind_direction" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_apparent_wind_speed , {
 "Apparent Wind Speed" , "btatt.apparent_wind_speed" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_apparent_wind_direction , {
 "Apparent Wind Direction" , "btatt.apparent_wind_direction" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_gust_factor , {
 "Gust Factor" , "btatt.gust_factor" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_pollen_concentration , {
 "Pollen Concentration" , "btatt.pollen_concentration" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uv_index , {
 "UV Index" , "btatt.uv_index" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_irradiance , {
 "Irradiance" , "btatt.irradiance" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rainfall , {
 "Rainfall" , "btatt.rainfall" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_wind_chill , {
 "Wind Chill" , "btatt.wind_chill" , FT_INT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_index , {
 "Heart Index" , "btatt.heart_index" , FT_INT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_dew_point , {
 "Dew Point" , "btatt.dew_point" , FT_INT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags , {
 "Flags" , "btatt.descriptor_value_changed.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags_reserved , {
 "Reserved" , "btatt.descriptor_value_changed.flags.reserved" , FT_BOOLEAN , 16 , NULL , 0xF800 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags_change_to_characteristic_user_description_descriptor , {
 "Change to Characteristic User Description Descriptor" , "btatt.descriptor_value_changed.flags.change_to_characteristic_user_description_descriptor" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags_change_to_es_measurement_descriptor , {
 "Change to ES Measurement Descriptor" , "btatt.descriptor_value_changed.flags.change_to_es_measurement_descriptor" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags_change_to_es_configuration_descriptor , {
 "Change to ES Configuration Descriptor" , "btatt.descriptor_value_changed.flags.change_to_es_configuration_descriptor" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags_change_to_one_or_more_es_trigger_setting_descriptors , {
 "Change to One or More ES Trigger Setting Descriptors" , "btatt.descriptor_value_changed.flags.change_to_one_or_more_es_trigger_setting_descriptors" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_descriptor_value_changed_flags_source_of_change , {
 "Source of Change" , "btatt.descriptor_value_changed.flags.source_of_change" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_aerobic_heart_rate_lower_limit , {
 "Aerobic Heart Rate Lower Limit" , "btatt.aerobic_heart_rate_lower_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_aerobic_threshold , {
 "Aerobic Threshold" , "btatt.aerobic_threshold" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_age , {
 "Age" , "btatt.age" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_anaerobic_heart_rate_lower_limit , {
 "Anaerobic Heart Rate Lower Limit" , "btatt.anaerobic_heart_rate_lower_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_anaerobic_heart_rate_upper_limit , {
 "Anaerobic Heart Rate Upper Limit" , "btatt.anaerobic_heart_rate_upper_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_anaerobic_threshold , {
 "Anaerobic Threshold" , "btatt.anaerobic_threshold" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_aerobic_heart_rate_upper_limit , {
 "Aerobic Heart Rate Upper Limit" , "btatt.aerobic_heart_rate_upper_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_email_address , {
 "Email Address" , "btatt.email_address" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_fat_burn_heart_rate_lower_limit , {
 "Fat Burn Heart Rate Lower Limit" , "btatt.fat_burn_heart_rate_lower_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_fat_burn_heart_rate_upper_limit , {
 "Fat Burn Heart Rate Upper Limit" , "btatt.fat_burn_heart_rate_upper_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_first_name , {
 "First Name" , "btatt.first_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_five_zone_heart_rate_limits_very_light_light_limit , {
 "Very Light/Light Limit" , "btatt.five_zone_heart_rate_limits.very_light_light_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_five_zone_heart_rate_limits_light_moderate_limit , {
 "Light/Moderate Limit," , "btatt.five_zone_heart_rate_limits.light_moderate_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_five_zone_heart_rate_limits_moderate_hard_limit , {
 "Moderate/Hard Limit" , "btatt.five_zone_heart_rate_limits.moderate_hard_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_five_zone_heart_rate_limits_hard_maximum_limit , {
 "Hard/Maximum Limit" , "btatt.five_zone_heart_rate_limits.hard_maximum_limit" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_gender , {
 "Gender" , "btatt.gender" , FT_UINT8 , BASE_HEX , VALS ( gender_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_max , {
 "Heart Rate Max" , "btatt.heart_rate_max" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_height , {
 "Height" , "btatt.height" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_hip_circumference , {
 "Hip Circumference" , "btatt.hip_circumference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_last_name , {
 "Last Name" , "btatt.last_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_maximum_recommended_heart_rate , {
 "Maximum Recommended Heart Rate" , "btatt.maximum_recommended_heart_rate" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_resting_heart_rate , {
 "Resting Heart Rate" , "btatt.resting_heart_rate" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_sport_type_for_aerobic_and_anaerobic_thresholds , {
 "Sport Type for Aerobic and Anaerobic Thresholds" , "btatt.sport_type_for_aerobic_and_anaerobic_thresholds" , FT_UINT8 , BASE_DEC , VALS ( sport_type_for_aerobic_and_anaerobic_thresholds_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_three_zone_heart_rate_limits_light_moderate , {
 "Three zone Heart Rate Limits - Light (Fat burn) / Moderate (Aerobic) Limit" , "btatt.three_zone_heart_rate_limits.light_moderate" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_three_zone_heart_rate_limits_moderate_hard , {
 "Three zone Heart Rate Limits - Moderate (Aerobic) / Hard (Anaerobic) Limit" , "btatt.three_zone_heart_rate_limits.moderate_hard" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_two_zone_heart_rate_limit_fat_burn_fitness , {
 "Two zone Heart Rate Limit - Fat burn / Fitness Limit" , "btatt.two_zone_heart_rate_limit.fat_burn_fitness" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_vo2_max , {
 "VO2 Max" , "btatt.vo2_max" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_waist_circumference , {
 "Waist Circumference" , "btatt.waist_circumference" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight , {
 "Weight" , "btatt.weight" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_database_change_increment , {
 "Database Change Increment" , "btatt.database_change_increment" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_user_index , {
 "User Index" , "btatt.user_index" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_magnetic_flux_density_x , {
 "X" , "btatt.hf_btatt_magnetic_flux_density.x" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_magnetic_flux_density_y , {
 "Y" , "btatt.hf_btatt_magnetic_flux_density.y" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_magnetic_flux_density_z , {
 "Z" , "btatt.hf_btatt_magnetic_flux_density.z" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_language , {
 "Language" , "btatt.language" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_barometric_pressure_trend , {
 "Barometric Pressure Trend" , "btatt.barometric_pressure_trend" , FT_UINT8 , BASE_DEC , VALS ( barometric_pressure_trend_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_central_address_resolution , {
 "Central Address Resolution" , "btatt.central_address_resolution" , FT_UINT8 , BASE_DEC , VALS ( central_address_resolution_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_resolvable_private_address , {
 "Resolvable Private Address" , "btatt.resolvable_private_address" , FT_UINT8 , BASE_DEC , VALS ( resolvable_private_address_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature , {
 "Cycling Power Feature" , "btatt.cycling_power_feature" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_reserved , {
 "Reserved" , "btatt.cycling_power_feature.reserved" , FT_UINT32 , BASE_HEX , NULL , 0xFFF80000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_factory_calibration_date , {
 "Factory Calibration Date" , "btatt.cycling_power_feature.factory_calibration_date" , FT_BOOLEAN , 32 , NULL , 0x00040000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_instantaneous_measurement_direction , {
 "Instantaneous Measurement Direction" , "btatt.cycling_power_feature.instantaneous_measurement_direction" , FT_BOOLEAN , 32 , NULL , 0x00020000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_sensor_measurement_context , {
 "Sensor Measurement Context" , "btatt.cycling_power_feature.sensor_measurement_context" , FT_UINT32 , BASE_HEX , VALS ( cycling_power_feature_sensor_measurement_context_vals ) , 0x00010000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_span_length_adjustment , {
 "Span Length Adjustment" , "btatt.cycling_power_feature.span_length_adjustment" , FT_BOOLEAN , 32 , NULL , 0x00008000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_chain_weight_adjustment , {
 "Chain Weight Adjustment" , "btatt.cycling_power_feature.chain_weight_adjustment" , FT_BOOLEAN , 32 , NULL , 0x00004000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_chain_length_adjustment , {
 "Chain Length Adjustment" , "btatt.cycling_power_feature.chain_length_adjustment" , FT_BOOLEAN , 32 , NULL , 0x00002000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_crank_length_adjustment , {
 "Crank Length Adjustment" , "btatt.cycling_power_feature.crank_length_adjustment" , FT_BOOLEAN , 32 , NULL , 0x00001000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_multiple_sensor_locations , {
 "Multiple Sensor Locations" , "btatt.cycling_power_feature.multiple_sensor_locations" , FT_BOOLEAN , 32 , NULL , 0x00000800 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_cycling_power_measurement_characteristic_content_masking , {
 "Cycling Power Measurement Characteristic Content Masking" , "btatt.cycling_power_feature.cycling_power_measurement_characteristic_content_masking" , FT_BOOLEAN , 32 , NULL , 0x00000400 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_offset_compensation , {
 "Offset Compensation" , "btatt.cycling_power_feature.offset_compensation" , FT_BOOLEAN , 32 , NULL , 0x00000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_offset_compensation_indicator , {
 "Offset Compensation Indicator" , "btatt.cycling_power_feature.offset_compensation_indicator" , FT_BOOLEAN , 32 , NULL , 0x00000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_accumulated_energy , {
 "Accumulated Energy" , "btatt.cycling_power_feature.accumulated_energy" , FT_BOOLEAN , 32 , NULL , 0x00000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_top_and_bottom_dead_spot_angles , {
 "Top and Bottom Dead Spot Angles" , "btatt.cycling_power_feature.top_and_bottom_dead_spot_angles" , FT_BOOLEAN , 32 , NULL , 0x00000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_extreme_angles , {
 "Extreme Angles" , "btatt.cycling_power_feature.extreme_angles" , FT_BOOLEAN , 32 , NULL , 0x00000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_extreme_magnitudes , {
 "Extreme Magnitudes" , "btatt.cycling_power_feature.extreme_magnitudes" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_crank_revolution_data , {
 "Crank Revolution Data" , "btatt.cycling_power_feature.crank_revolution_data" , FT_BOOLEAN , 32 , NULL , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_wheel_revolution_data , {
 "Wheel Revolution Data" , "btatt.cycling_power_feature.wheel_revolution_data" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_accumulated_torque , {
 "Accumulated Torque" , "btatt.cycling_power_feature.accumulated_torque" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_feature_pedal_power_balance , {
 "Pedal Power Balance" , "btatt.cycling_power_feature.pedal_power_balance" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature , {
 "LN Feature" , "btatt.ln_feature" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_reserved , {
 "Reserved" , "btatt.ln_feature.reserved" , FT_UINT32 , BASE_HEX , NULL , 0xFFE00000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_position_status , {
 "Position Status" , "btatt.ln_feature.position_status" , FT_BOOLEAN , 32 , NULL , 0x00100000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_elevation_setting , {
 "Elevation Setting," , "btatt.ln_feature.elevation_setting" , FT_BOOLEAN , 32 , NULL , 0x00080000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_fix_rate_setting , {
 "Fix Rate Setting" , "btatt.ln_feature.fix_rate_setting" , FT_BOOLEAN , 32 , NULL , 0x00040000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_location_and_speed_characteristic_content_masking , {
 "Location and Speed Characteristic Content Masking" , "btatt.ln_feature.location_and_speed_characteristic_content_masking" , FT_BOOLEAN , 32 , NULL , 0x00020000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_vertical_dilution_of_precision , {
 "Vertical Dilution of Precision" , "btatt.ln_feature.vertical_dilution_of_precision" , FT_BOOLEAN , 32 , NULL , 0x00010000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_horizontal_dilution_of_precision , {
 "Horizontal Dilution of Precision" , "btatt.ln_feature.horizontal_dilution_of_precision" , FT_BOOLEAN , 32 , NULL , 0x00008000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_estimated_vertical_position_error , {
 "Estimated Vertical Position Error" , "btatt.ln_feature.estimated_vertical_position_error" , FT_BOOLEAN , 32 , NULL , 0x00004000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_estimated_horizontal_position_error , {
 "Estimated Horizontal Position Error" , "btatt.ln_feature.estimated_horizontal_position_error" , FT_BOOLEAN , 32 , NULL , 0x00002000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_time_to_first_fix , {
 "Time to First Fix" , "btatt.ln_feature.time_to_first_fix" , FT_BOOLEAN , 32 , NULL , 0x00001000 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_number_of_beacons_in_view , {
 "Number of Beacons in View" , "btatt.ln_feature.number_of_beacons_in_view" , FT_BOOLEAN , 32 , NULL , 0x00000800 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_number_of_beacons_in_solution , {
 "Number of Beacons in Solution" , "btatt.ln_feature.number_of_beacons_in_solution" , FT_BOOLEAN , 32 , NULL , 0x00000400 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_estimated_time_of_arrival , {
 "Estimated Time of Arrival" , "btatt.ln_feature.estimated_time_of_arrival" , FT_BOOLEAN , 32 , NULL , 0x00000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_remaining_vertical_distance , {
 "Remaining Vertical Distance" , "btatt.ln_feature.remaining_vertical_distance" , FT_BOOLEAN , 32 , NULL , 0x00000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_remaining_distance , {
 "Remaining Distance" , "btatt.ln_feature.remaining_distance" , FT_BOOLEAN , 32 , NULL , 0x00000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_utc_time , {
 "UTC Time" , "btatt.ln_feature.utc_time" , FT_BOOLEAN , 32 , NULL , 0x00000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_rolling_time , {
 "Rolling Time" , "btatt.ln_feature.rolling_time" , FT_BOOLEAN , 32 , NULL , 0x00000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_heading , {
 "Heading" , "btatt.ln_feature.heading" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_elevation , {
 "Elevation" , "btatt.ln_feature.elevation" , FT_BOOLEAN , 32 , NULL , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_location , {
 "Location" , "btatt.ln_feature.location" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_total_distance , {
 "Total Distance" , "btatt.ln_feature.total_distance" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_feature_instantaneous_speed , {
 "Instantaneous Speed" , "btatt.ln_feature.instantaneous_speed" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature , {
 "Body Composition Feature" , "btatt.body_composition_feature" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_reserved , {
 "Reserved" , "btatt.body_composition_feature.reserved" , FT_UINT32 , BASE_HEX , NULL , 0xFFFC0000 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_height_measurement_resolution , {
 "Height Measurement Resolution" , "btatt.body_composition_feature.height_measurement_resolution" , FT_UINT32 , BASE_HEX , VALS ( body_composition_feature_height_measurement_resolution_vals ) , 0x00038000 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_mass_measurement_resolution , {
 "Mass Measurement Resolution" , "btatt.body_composition_feature.mass_measurement_resolution" , FT_UINT32 , BASE_HEX , VALS ( body_composition_feature_mass_measurement_resolution_vals ) , 0x00007800 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_height , {
 "Height" , "btatt.body_composition_feature.height" , FT_BOOLEAN , 32 , NULL , 0x00000400 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_weight , {
 "Weight" , "btatt.body_composition_feature.weight" , FT_BOOLEAN , 32 , NULL , 0x00000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_impedance , {
 "Impedance" , "btatt.body_composition_feature.impedance" , FT_BOOLEAN , 32 , NULL , 0x00000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_body_water_mass , {
 "Body Water Mass" , "btatt.body_composition_feature.body_water_mass" , FT_BOOLEAN , 32 , NULL , 0x00000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_soft_lean_mass , {
 "Soft Lean Mass" , "btatt.body_composition_feature.soft_lean_mass" , FT_BOOLEAN , 32 , NULL , 0x00000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_fat_free_mass , {
 "Fat Free Mass" , "btatt.body_composition_feature.fat_free_mass" , FT_BOOLEAN , 32 , NULL , 0x00000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_muscle_mass , {
 "Muscle Mass" , "btatt.body_composition_feature.muscle_mass" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_muscle_percentage , {
 "Muscle Percentage" , "btatt.body_composition_feature.muscle_percentage" , FT_BOOLEAN , 32 , NULL , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_basal_metabolism , {
 "Basal Metabolism" , "btatt.body_composition_feature.basal_metabolism" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_multiple_users , {
 "Multiple Users" , "btatt.body_composition_feature.multiple_users" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_feature_timestamp , {
 "Timestamp" , "btatt.body_composition_feature.timestamp" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature , {
 "Weight Scale Feature" , "btatt.weight_scale_feature" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature_reserved , {
 "Reserved" , "btatt.weight_scale_feature.reserved" , FT_UINT32 , BASE_HEX , NULL , 0xFFFFFC00 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature_height_measurement_resolution , {
 "Height Measurement Resolution" , "btatt.weight_scale_feature.height_measurement_resolution" , FT_UINT32 , BASE_HEX , VALS ( weight_scale_feature_height_measurement_resolution_vals ) , 0x00000380 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature_weight_measurement_resolution , {
 "Mass Measurement Resolution" , "btatt.weight_scale_feature.weight_measurement_resolution" , FT_UINT32 , BASE_HEX , VALS ( weight_scale_feature_weight_measurement_resolution_vals ) , 0x000000078 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature_bmi , {
 "BMI" , "btatt.weight_scale_feature.bmi" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature_multiple_users , {
 "Multiple Users" , "btatt.weight_scale_feature.multiple_users" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_scale_feature_timestamp , {
 "Timestamp" , "btatt.weight_scale_feature.timestamp" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags , {
 "Flags" , "btatt.glucose_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags_reserved , {
 "Reserved" , "btatt.glucose_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags_context_information_follows , {
 "Context Information Follows" , "btatt.glucose_measurement.flags.context_information_follows" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags_sensor_status_annunciation_present , {
 "Sensor Status Annunciation Present" , "btatt.glucose_measurement.flags.sensor_status_annunciation_present" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags_glucose_concentration_units , {
 "Glucose Concentration Units" , "btatt.glucose_measurement.flags.glucose_concentration_units" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_flags_glucose_concentration_units_vals ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags_glucose_concentration_type_and_sample_location_present , {
 "Glucose Concentration, Type and Sample Location Present" , "btatt.glucose_measurement.flags.glucose_concentration_type_and_sample_location_present" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_flags_time_offset_present , {
 "Time Offset Present" , "btatt.glucose_measurement.flags.time_offset_present" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sequence_number , {
 "Sequence Number" , "btatt.glucose_measurement.sequence_number" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_base_time , {
 "Base Time" , "btatt.glucose_measurement.base_time" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_time_offset , {
 "Time Offset" , "btatt.glucose_measurement.time_offset" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_glucose_concentration_kg_per_l , {
 "Glucose Concentration [kg/l]" , "btatt.glucose_measurement.glucose_concentration.kg_per_l" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_glucose_concentration_mol_per_l , {
 "Glucose Concentration [mol/l]" , "btatt.glucose_measurement.glucose_concentration.mol_per_l" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_type_and_sample_location , {
 "Type and Sample Location" , "btatt.glucose_measurement.type_and_sample_location" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_type_and_sample_location_type , {
 "Type" , "btatt.glucose_measurement.type_and_sample_location.type" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_type_and_sample_location_type_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_type_and_sample_location_sample_location , {
 "Sample Location" , "btatt.glucose_measurement.type_and_sample_location.sample_location" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_type_and_sample_location_sample_location_vals ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation , {
 "Sensor Status Annunciation" , "btatt.glucose_measurement.sensor_status_annunciation" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_reserved , {
 "Reserved" , "btatt.glucose_measurement.sensor_status_annunciation.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xF000 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_time_fault , {
 "Time fault has occurred in the sensor and time may be inaccurate" , "btatt.glucose_measurement.sensor_status_annunciation.time_fault" , FT_BOOLEAN , 16 , NULL , 0x0800 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_general_fault , {
 "General device fault has occurred in the sensor" , "btatt.glucose_measurement.sensor_status_annunciation.general_fault" , FT_BOOLEAN , 16 , NULL , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_read_interrupted , {
 "Sensor read interrupted because strip was pulled too soon at time of measurement" , "btatt.glucose_measurement.sensor_status_annunciation.read_interrupted" , FT_BOOLEAN , 16 , NULL , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_temperature_too_low , {
 "Sensor temperature too low for valid test/result at time of measurement" , "btatt.glucose_measurement.sensor_status_annunciation.temperature_too_low" , FT_BOOLEAN , 16 , NULL , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_temperature_too_high , {
 "Sensor temperature too high for valid test/result at time of measurement" , "btatt.glucose_measurement.sensor_status_annunciation.temperature_too_high" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_result_too_lower , {
 "Sensor result lower than the device can process" , "btatt.glucose_measurement.sensor_status_annunciation.result_too_lower" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_result_too_high , {
 "Sensor result higher than the device can process" , "btatt.glucose_measurement.sensor_status_annunciation.result_too_high" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_strip_type_incorrect , {
 "Strip type incorrect for device" , "btatt.glucose_measurement.sensor_status_annunciation.strip_type_incorrect" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_strip_insertion_error , {
 "Strip insertion error" , "btatt.glucose_measurement.sensor_status_annunciation.strip_insertion_error" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_size_insufficient , {
 "Sample size for blood or control solution insufficient at time of measurement" , "btatt.glucose_measurement.sensor_status_annunciation.size_insufficient" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_fault , {
 "Sensor malfunction or faulting at time of measurement" , "btatt.glucose_measurement.sensor_status_annunciation.fault" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_sensor_status_annunciation_battery_low , {
 "Device battery low at time of measurement" , "btatt.glucose_measurement.sensor_status_annunciation.battery_low" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature , {
 "Bond Management Feature" , "btatt.bond_management_feature" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_feature_extension , {
 "Feature Extension" , "btatt.bond_management_feature.feature_extension" , FT_BOOLEAN , 24 , NULL , 0x800000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_reserved , {
 "Reserved" , "btatt.bond_management_feature.reserved" , FT_UINT24 , BASE_HEX , NULL , 0x780000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_identify_yourself , {
 "Identify Yourself" , "btatt.bond_management_feature.identify_yourself" , FT_BOOLEAN , 24 , NULL , 0x040000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_9 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.9" , FT_BOOLEAN , 24 , NULL , 0x020000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_remove_all_but_the_active_bond_on_le_transport_only_server , {
 "Remove all but the active bond on server (LE transport only)" , "btatt.bond_management_feature.remove_all_but_the_active_bond_on_le_transport_only_server" , FT_BOOLEAN , 24 , NULL , 0x010000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_8 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.8" , FT_BOOLEAN , 24 , NULL , 0x008000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_remove_all_but_the_active_bond_on_br_edr_transport_only_server , {
 "Remove all but the active bond on server (BR/EDR transport only)" , "btatt.bond_management_feature.remove_all_but_the_active_bond_on_br_edr_transport_only_server" , FT_BOOLEAN , 24 , NULL , 0x004000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_7 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.7" , FT_BOOLEAN , 24 , NULL , 0x002000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_remove_all_but_the_active_bond_on_br_edr_and_le_server , {
 "Remove all but the active bond on server (BR/EDR and LE)" , "btatt.bond_management_feature.remove_all_but_the_active_bond_on_br_edr_and_le_server" , FT_BOOLEAN , 24 , NULL , 0x001000 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_6 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.6" , FT_BOOLEAN , 24 , NULL , 0x000800 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_remove_all_bonds_on_le_transport_only_server , {
 "Remove all bonds on server (LE transport only)" , "btatt.bond_management_feature.remove_all_bonds_on_le_transport_only_server" , FT_BOOLEAN , 24 , NULL , 0x000400 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_5 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.5" , FT_BOOLEAN , 24 , NULL , 0x000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_remove_all_bonds_on_br_edr_transport_only_server , {
 "Remove all bonds on server (BR/EDR transport only)" , "btatt.bond_management_feature.remove_all_bonds_on_br_edr_transport_only_server" , FT_BOOLEAN , 24 , NULL , 0x000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_4 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.4" , FT_BOOLEAN , 24 , NULL , 0x000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_remove_all_bonds_on_br_edr_and_le_server , {
 "Remove all bonds on server (BR/EDR and LE)" , "btatt.bond_management_feature.remove_all_bonds_on_br_edr_and_le_server" , FT_BOOLEAN , 24 , NULL , 0x000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_3 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.3" , FT_BOOLEAN , 24 , NULL , 0x000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_delete_bond_of_current_le_transport_only_connection , {
 "Delete bond of current connection (LE transport only)" , "btatt.bond_management_feature.delete_bond_of_current_le_transport_only_connection" , FT_BOOLEAN , 24 , NULL , 0x000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_2 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.2" , FT_BOOLEAN , 24 , NULL , 0x000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_delete_bond_of_current_br_edr_transport_only_connection , {
 "Delete bond of current connection (BR/EDR transport only)" , "btatt.bond_management_feature.delete_bond_of_current_br_edr_transport_only_connection" , FT_BOOLEAN , 24 , NULL , 0x000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_authorization_code_required_for_feature_above_1 , {
 "Authorization Code Required for Feature Above" , "btatt.bond_management_feature.authorization_code_required_for_feature_above.1" , FT_BOOLEAN , 24 , NULL , 0x000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_delete_bond_of_current_br_edr_and_le_connection , {
 "Delete Bond of current connection (BR/EDR and LE)" , "btatt.bond_management_feature.delete_bond_of_current_br_edr_and_le_connection" , FT_BOOLEAN , 24 , NULL , 0x000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_nth , {
 "Extended Features" , "btatt.bond_management_feature.nth" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_nth_feature_extension , {
 "Feature Extension" , "btatt.bond_management_feature.nth.feature_extension" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_feature_nth_reserved , {
 "Reserved" , "btatt.bond_management_feature.nth.reserved" , FT_UINT8 , BASE_HEX , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_control_point_opcode , {
 "Opcode" , "btatt.bond_management_control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( bond_management_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_bond_management_control_point_authorization_code , {
 "Authorization Code" , "btatt.bond_management_control_point.authorization_code" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_flags , {
 "Sensor Status Annunciation" , "btatt.temperature_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_flags_reserved , {
 "Reserved" , "btatt.temperature_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xF8 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_flags_temperature_type , {
 "Temperature Type" , "btatt.temperature_measurement.flags.temperature_type" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_flags_timestamp , {
 "Timestamp" , "btatt.temperature_measurement.flags.timestamp" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_flags_temperature_unit , {
 "Temperature Unit" , "btatt.temperature_measurement.flags.temperature_unit" , FT_UINT8 , BASE_HEX , VALS ( temperature_measurement_flags_temperature_unit_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_value_celsius , {
 "Value [Celsius]" , "btatt.temperature_measurement.value.celsius" , FT_IEEE_11073_FLOAT , BASE_FLOAT , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_value_fahrenheit , {
 "Value [Fahrenheit]" , "btatt.temperature_measurement.value.fahrenheit" , FT_IEEE_11073_FLOAT , BASE_FLOAT , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btatt_temperature_measurement_timestamp , {
 "Timestamp" , "btatt.temperature_measurement.timestamp" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags , {
 "Glucose Measurement Context" , "btatt.glucose_measurement_context.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_extended_flags , {
 "Extended Flags" , "btatt.glucose_measurement_context.flags.extended_flags" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_hba1c , {
 "HbA1c" , "btatt.glucose_measurement_context.flags.hba1c" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_medication_value_units , {
 "Medication Value Units" , "btatt.glucose_measurement_context.flags.medication_value_units" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_context_flags_medication_value_units_vals ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_medication_id_and_medication , {
 "Medication ID And Medication" , "btatt.glucose_measurement_context.flags.medication_id_and_medication" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_exercise_duration_and_exercise_intensity , {
 "Exercise Duration And Exercise Intensity" , "btatt.glucose_measurement_context.flags.exercise_duration_and_exercise_intensity" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_tester_health , {
 "Tester Health" , "btatt.glucose_measurement_context.flags.tester_health" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_meal , {
 "Meal" , "btatt.glucose_measurement_context.flags.meal" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_flags_carbohydrate_id_and_carbohydrate , {
 "Carbohydrate ID And Carbohydrate" , "btatt.glucose_measurement_context.flags.carbohydrate_id_and_carbohydrate" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_sequence_number , {
 "Sequence Number" , "btatt.glucose_measurement_context.sequence_number" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_extended_flags , {
 "Extended Flags" , "btatt.glucose_measurement_context.extended_flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_extended_flags_reserved , {
 "Reserved" , "btatt.glucose_measurement_context.extended_flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xFF , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_carbohydrate_id , {
 "Carbohydrate ID" , "btatt.glucose_measurement_context.carbohydrate_id" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_context_carbohydrate_id_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_carbohydrate_kg , {
 "Carbohydrate [kg]" , "btatt.glucose_measurement_context.carbohydrate.kg" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_meal , {
 "Meal" , "btatt.glucose_measurement_context.meal" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_context_meal_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_tester_health , {
 "Tester and Health" , "btatt.glucose_measurement_context.tester_and_health" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_tester , {
 "Tester" , "btatt.glucose_measurement_context.tester_and_health.tester" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_context_tester_vals ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_health , {
 "Health" , "btatt.glucose_measurement_context.tester_and_health.health" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_context_health_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_exercise_duration , {
 "Exercise Duration" , "btatt.glucose_measurement_context.exercise_duration" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_exercise_intensity , {
 "Exercise Intensity" , "btatt.glucose_measurement_context.exercise_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_medication_id , {
 "Medication ID" , "btatt.glucose_measurement_context.medication_id" , FT_UINT8 , BASE_HEX , VALS ( glucose_measurement_context_medication_id_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_medication_l , {
 "Medication [l]" , "btatt.glucose_measurement_context.medication.l" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_medication_kg , {
 "Medication [kg]" , "btatt.glucose_measurement_context.medication.kg" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_glucose_measurement_context_hba1c , {
 "HbA1c" , "btatt.glucose_measurement_context.hba1c" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags , {
 "Flags" , "btatt.blood_pressure_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags_reserved , {
 "Reserved" , "btatt.blood_pressure_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags_measurement_status , {
 "Measurement Status" , "btatt.blood_pressure_measurement.flags.measurement_status" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags_user_id , {
 "User ID" , "btatt.blood_pressure_measurement.flags.user_id" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags_pulse_rate , {
 "Pulse Rate" , "btatt.blood_pressure_measurement.flags.pulse_rate" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags_timestamp , {
 "Timestamp" , "btatt.blood_pressure_measurement.flags.timestamp" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_flags_unit , {
 "Unit" , "btatt.blood_pressure_measurement.flags.unit" , FT_UINT8 , BASE_HEX , VALS ( blood_pressure_measurement_unit_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_compound_value_systolic_kpa , {
 "Systolic [kPa]" , "btatt.blood_pressure_measurement.compound_value.systolic.kpa" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_compound_value_diastolic_kpa , {
 "Diastolic [kPa]" , "btatt.blood_pressure_measurement.compound_value.diastolic.kpa" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_compound_value_mean_arterial_pressure_kpa , {
 "Arterial Pressure [kPa]" , "btatt.blood_pressure_measurement.compound_value.arterial_pressure.kpa" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_compound_value_systolic_mmhg , {
 "Systolic [mmHg]" , "btatt.blood_pressure_measurement.compound_value.systolic.mmhg" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_compound_value_diastolic_mmhg , {
 "Diastolic [mmHg]" , "btatt.blood_pressure_measurement.compound_value.diastolic.mmhg" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_compound_value_mean_arterial_pressure_mmhg , {
 "Arterial Pressure [mmHg]" , "btatt.blood_pressure_measurement.compound_value.arterial_pressure.mmhg" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_timestamp , {
 "Timestamp" , "btatt.blood_pressure_measurement.compound_value.timestamp" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_pulse_rate , {
 "Pulse Rate" , "btatt.blood_pressure_measurement.pulse_rate" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_user_id , {
 "User ID" , "btatt.blood_pressure_measurement.user_id" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status , {
 "Flags" , "btatt.blood_pressure_measurement.status" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status_reserved , {
 "Reserved" , "btatt.blood_pressure_measurement.status.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFFC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status_improper_measurement_position , {
 "Improper Measurement Position" , "btatt.blood_pressure_measurement.status.improper_measurement_position" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status_pulse_rate_range_detection , {
 "Pulse_Rate Range Detection" , "btatt.blood_pressure_measurement.status.pulse_rate_range_detection" , FT_UINT16 , BASE_HEX , VALS ( blood_pressure_measurement_status_pulse_rate_range_detection_vals ) , 0x0018 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status_irregular_pulse , {
 "Irregular Pulse" , "btatt.blood_pressure_measurement.status.irregular_pulse" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status_cuff_fit_too_loose , {
 "Cuff Fit too Loose" , "btatt.blood_pressure_measurement.status.cuff_fit_too_loose" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_blood_pressure_measurement_status_body_movement , {
 "Body Movement" , "btatt.blood_pressure_measurement.status.body_movement" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags , {
 "Flags" , "btatt.heart_rate_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags_reserved , {
 "Reserved" , "btatt.heart_rate_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags_rr_interval , {
 "RR Interval" , "btatt.heart_rate_measurement.flags.rr_interval" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags_energy_expended , {
 "Energy Expended" , "btatt.heart_rate_measurement.flags.energy_expended" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags_sensor_contact_status_support , {
 "Sensor Support" , "btatt.heart_rate_measurement.flags.sensor_contact_status.support" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags_sensor_contact_status_contact , {
 "Sensor Contact" , "btatt.heart_rate_measurement.flags.sensor_contact_status.contact" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_flags_value_16 , {
 "Value is UINT16" , "btatt.heart_rate_measurement.flags.value_16" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_value_8 , {
 "Value" , "btatt.heart_rate_measurement.value.8" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_value_16 , {
 "Value" , "btatt.heart_rate_measurement.value.16" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_energy_expended , {
 "Energy Expended" , "btatt.heart_rate_measurement.energy_expended" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_rr_intervals , {
 "RR Intervals" , "btatt.heart_rate_measurement.rr_intervals" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_heart_rate_measurement_rr_interval , {
 "RR Interval" , "btatt.heart_rate_measurement.rr_interval" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_opcode , {
 "Opcode" , "btatt.record_access_control_point.opcode" , FT_UINT8 , BASE_DEC , VALS ( record_access_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_operator , {
 "Operator" , "btatt.record_access_control_point.operator" , FT_UINT8 , BASE_DEC , VALS ( record_access_control_point_operator_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_operand , {
 "Operand" , "btatt.record_access_control_point.operand" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_operand_filter_type , {
 "Filter Type" , "btatt.record_access_control_point.operand.filter_type" , FT_UINT8 , BASE_DEC , VALS ( record_access_control_point_operand_filter_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_operand_min_time_offset , {
 "Min Time Offset" , "btatt.record_access_control_point_operand.min_time_offset" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_operand_max_time_offset , {
 "Max Time Offset" , "btatt.record_access_control_point_operand.max_time_offset" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_operand_number_of_records , {
 "Number of Records" , "btatt.record_access_control_point_operand.number_of_records" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_request_opcode , {
 "Request Opcode" , "btatt.record_access_control_point.request_opcode" , FT_UINT8 , BASE_DEC , VALS ( record_access_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_record_access_control_point_response_code , {
 "Response Opcode" , "btatt.record_access_control_point.response_code" , FT_UINT8 , BASE_DEC , VALS ( record_access_control_point_response_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_value_trigger_setting_condition , {
 "Condition" , "btatt.value_trigger_setting.condition" , FT_UINT8 , BASE_DEC , VALS ( value_trigger_setting_condition_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_value_trigger_setting_analog , {
 "Analog" , "btatt.value_trigger_setting.analog" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_value_trigger_setting_analog_one , {
 "Analog One" , "btatt.value_trigger_setting.analog_one" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_value_trigger_setting_analog_two , {
 "Analog Two" , "btatt.value_trigger_setting.analog_two" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_digital , {
 "Digital" , "btatt.digital" , FT_UINT8 , BASE_DEC , VALS ( digital_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_analog , {
 "Analog" , "btatt.analog" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_name , {
 "Location Name" , "btatt.location_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uncertainty , {
 "Uncertainty" , "btatt.uncertainty" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uncertainty_reserved , {
 "Reserved" , "btatt.uncertainty.reserved" , FT_UINT8 , BASE_HEX , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_uncertainty_precision , {
 "Precision" , "btatt.uncertainty.precision" , FT_UINT8 , BASE_HEX , VALS ( btatt_ips_uncertainty_precision_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_btatt_uncertainty_update_time , {
 "Update Time" , "btatt.uncertainty.update_time" , FT_UINT8 , BASE_HEX , VALS ( btatt_ips_uncertainty_update_time_vals ) , 0x0E , NULL , HFILL }
 }
 , {
 & hf_btatt_uncertainty_stationary , {
 "Stationary" , "btatt.uncertainty.stationary" , FT_UINT8 , BASE_HEX , VALS ( btatt_ips_uncertainty_stationary_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_latitude , {
 "Latitude" , "btatt.latitude" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_longitude , {
 "Longitude" , "btatt.longitude" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_local_north_coordinate , {
 "Local North Coordinate" , "btatt.local_north_coordinate" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_local_east_coordinate , {
 "Local East Coordinate" , "btatt.local_east_coordinate" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_floor_number , {
 "Floor Number" , "btatt.floor_number" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_altitude , {
 "Altitude" , "btatt.altitude" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration , {
 "Indoor Positioning Configuration" , "btatt.indoor_positioning_configuration" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_reserved , {
 "Reserved" , "btatt.indoor_positioning_configuration.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_location_name , {
 "Location Name" , "btatt.indoor_positioning_configuration.location_name" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_uncertainty , {
 "Uncertainty" , "btatt.indoor_positioning_configuration.uncertainty" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_floor_number , {
 "Floor Number" , "btatt.indoor_positioning_configuration.floor_number" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_altitude , {
 "Altitude" , "btatt.indoor_positioning_configuration.altitude" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_tx_power , {
 "Tx Power" , "btatt.indoor_positioning_configuration.tx_power" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_coordinate_system , {
 "Coordinate System" , "btatt.indoor_positioning_configuration.coordinate_system" , FT_UINT8 , BASE_HEX , VALS ( btatt_ips_coordinate_system ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_indoor_positioning_configuration_coordinates , {
 "Coordinates" , "btatt.indoor_positioning_configuration.coordinates" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_number_of_digitals , {
 "Number of Digitals" , "btatt.number_of_digitals" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_trigger_setting_condition , {
 "Condition" , "btatt.time_trigger_setting.condition" , FT_UINT8 , BASE_HEX , VALS ( time_trigger_setting_condition_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_trigger_setting_value , {
 "Value" , "btatt.time_trigger_setting.value" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_trigger_setting_value_count , {
 "Count" , "btatt.time_trigger_setting.count" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_time_trigger_setting_value_time_interval , {
 "Time Interval" , "btatt.time_trigger_setting.time_interval" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_flags , {
 "Flags" , "btatt.rsc_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_flags_reserved , {
 "Reserved" , "btatt.rsc_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xF8 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_flags_type_of_movement , {
 "Type of Movement" , "btatt.rsc_measurement.flags.type_of_movement" , FT_UINT8 , BASE_HEX , VALS ( rsc_measurement_flags_type_of_movement_vals ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_flags_total_distance_present , {
 "Total Distance Present" , "btatt.rsc_measurement.flags.total_distance_present" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_flags_instantaneous_stride_length_present , {
 "Instantaneous Stride Length Present" , "btatt.rsc_measurement.flags.instantaneous_stride_length_present" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_instantaneous_speed , {
 "Instantaneous Speed" , "btatt.rsc_measurement.instantaneous_speed" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_instantaneous_cadence , {
 "Instantaneous Cadence" , "btatt.rsc_measurement.instantaneous_cadence" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_instantaneous_stride_length , {
 "Instantaneous Stride Length" , "btatt.rsc_measurement.instantaneous_stride_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_rsc_measurement_total_distance , {
 "Total Distance" , "btatt.rsc_measurement.total_distance" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_sc_control_point_opcode , {
 "Opcode" , "btatt.sc_control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( sc_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_sc_control_point_request_opcode , {
 "Request Opcode" , "btatt.sc_control_point.request_opcode" , FT_UINT8 , BASE_HEX , VALS ( sc_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_sc_control_point_cumulative_value , {
 "Cumulative Value" , "btatt.sc_control_point.cumulative_value" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_sc_control_point_response_value , {
 "Response Value" , "btatt.sc_control_point.response_value" , FT_UINT8 , BASE_HEX , VALS ( sc_control_point_response_value_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags , {
 "Flags" , "btatt.cycling_power_measurement.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_reserved , {
 "Reserved" , "btatt.cycling_power_measurement.flags.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xE000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_offset_compensation_indicator , {
 "Offset Compensation Indicator" , "btatt.cycling_power_measurement.flags.offset_compensation_indicator" , FT_BOOLEAN , 16 , NULL , 0x1000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_accumulated_energy , {
 "Accumulated Energy" , "btatt.cycling_power_measurement.flags.accumulated_energy" , FT_BOOLEAN , 16 , NULL , 0x0800 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_bottom_dead_spot_angle , {
 "Bottom Dead Spot Angle" , "btatt.cycling_power_measurement.flags.bottom_dead_spot_angle" , FT_BOOLEAN , 16 , NULL , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_top_dead_spot_angle , {
 "Top Dead Spot Angle" , "btatt.cycling_power_measurement.flags.top_dead_spot_angle" , FT_BOOLEAN , 16 , NULL , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_extreme_angles , {
 "Extreme_angles" , "btatt.cycling_power_measurement.flags.extreme_angles" , FT_BOOLEAN , 16 , NULL , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_extreme_torque_magnitudes , {
 "Extreme Torque Magnitudes" , "btatt.cycling_power_measurement.flags.extreme_torque_magnitudes" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_extreme_force_magnitudes , {
 "Extreme Force Magnitudes" , "btatt.cycling_power_measurement.flags.extreme_force_magnitudes" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_crank_revolution_data , {
 "Crank Revolution Data" , "btatt.cycling_power_measurement.flags.crank_revolution_data" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_wheel_revolution_data , {
 "Wheel Revolution Data" , "btatt.cycling_power_measurement.flags.wheel_revolution_data" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_accumulated_torque_source , {
 "accumulated_torque_source" , "btatt.cycling_power_measurement.flags.accumulated_torque_source" , FT_UINT16 , BASE_HEX , VALS ( cycling_power_measurement_flags_accumulated_torque_source_vals ) , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_accumulated_torque , {
 "Accumulated Torque" , "btatt.cycling_power_measurement.flags.accumulated_torque" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_pedal_power_balance_reference , {
 "Pedal Power Balance Reference" , "btatt.cycling_power_measurement.flags.pedal_power_balance_reference" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_flags_pedal_power_balance , {
 "Pedal Power Balance" , "btatt.cycling_power_measurement.flags.pedal_power_balance" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_instantaneous_power , {
 "Instantaneous Power" , "btatt.cycling_power_measurement.instantaneous_power" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_pedal_power_balance , {
 "Pedal Power Balance" , "btatt.cycling_power_measurement.pedal_power_balance" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_accumulated_torque , {
 "Accumulated Torque" , "btatt.cycling_power_measurement.accumulated_torque" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_wheel_revolution_data_cumulative_wheel_revolutions , {
 "Wheel Revolution Data Cumulative Wheel Revolutions" , "btatt.cycling_power_measurement.wheel_revolution_data_cumulative_wheel_revolutions" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_wheel_revolution_data_last_wheel_event_time , {
 "Wheel Revolution Data Last Wheel Event Time" , "btatt.cycling_power_measurement.wheel_revolution_data_last_wheel_event_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_crank_revolution_data_cumulative_crank_revolutions , {
 "Crank Revolution Data Cumulative Crank Revolutions" , "btatt.cycling_power_measurement.crank_revolution_data_cumulative_crank_revolutions" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_crank_revolution_data_last_crank_event_time , {
 "Crank Revolution Data Last Crank Event Time" , "btatt.cycling_power_measurement.crank_revolution_data_last_crank_event_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_force_magnitudes_maximum_force_magnitude , {
 "Extreme Force Magnitudes Maximum Force Magnitude" , "btatt.cycling_power_measurement.extreme_force_magnitudes_maximum_force_magnitude" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_force_magnitudes_minimum_force_magnitude , {
 "Extreme Force Magnitudes Minimum Force Magnitude" , "btatt.cycling_power_measurement.extreme_force_magnitudes_minimum_force_magnitude" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_torque_magnitudes_maximum_torque_magnitude , {
 "Extreme Torque Magnitudes Maximum Torque Magnitude" , "btatt.cycling_power_measurement.extreme_torque_magnitudes_maximum_torque_magnitude" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_torque_magnitudes_minimum_torque_magnitude , {
 "Extreme Torque Magnitudes Minimum Torque Magnitude" , "btatt.cycling_power_measurement.extreme_torque_magnitudes_minimum_torque_magnitude" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_angles , {
 "Extreme Angles" , "btatt.cycling_power_measurement.extreme_angles" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_angles_maximum , {
 "Minimum" , "btatt.cycling_power_measurement.extreme_angles.maximum" , FT_UINT24 , BASE_DEC , NULL , 0xFFF000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_extreme_angles_minimum , {
 "Maximum" , "btatt.cycling_power_measurement.extreme_angles.minimum" , FT_UINT24 , BASE_DEC , NULL , 0x000FFF , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_top_dead_spot_angle , {
 "Top Dead Spot Angle" , "btatt.cycling_power_measurement.top_dead_spot_angle" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_bottom_dead_spot_angle , {
 "Bottom Dead Spot Angle" , "btatt.cycling_power_measurement.bottom_dead_spot_angle" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_measurement_accumulated_energy , {
 "Accumulated Energy" , "btatt.cycling_power_measurement.accumulated_energy" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_flags , {
 "Flags" , "btatt.csc_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_flags_reserved , {
 "Reserved" , "btatt.csc_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xFC , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_flags_crank_revolution_data , {
 "Crank Revolution Data" , "btatt.csc_measurement.flags.crank_revolution_data" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_flags_wheel_revolution_data , {
 "Wheel Revolution Data" , "btatt.csc_measurement.flags.wheel_revolution_data" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_cumulative_wheel_revolutions , {
 "Cumulative Wheel Revolutions" , "btatt.csc_measurement.cumulative_wheel_revolutions" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_cumulative_crank_revolutions , {
 "Cumulative Crank Revolutions" , "btatt.csc_measurement.cumulative_crank_revolutions" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_csc_measurement_last_event_time , {
 "Last Event Time" , "btatt.csc_measurement.last_event_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags , {
 "Flags" , "btatt.csc_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags_reserved , {
 "Reserved" , "btatt.csc_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags_instantaneous_measurement_direction , {
 "Instantaneous Measurement Direction" , "btatt.cycling_power_vector.flags.instantaneous_measurement_direction" , FT_UINT8 , BASE_HEX , VALS ( cycling_power_vector_flags_instantaneous_measurement_direction_vals ) , 0x30 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags_instantaneous_torque_magnitude_array , {
 "Instantaneous Torque Magnitude Array" , "btatt.cycling_power_vector.flags.instantaneous_torque_magnitude_array" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags_instantaneous_force_magnitude_array , {
 "Instantaneous Force Magnitude Array" , "btatt.cycling_power_vector.flags.instantaneous_force_magnitude_array" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags_first_crank_measurement_angle , {
 "First Crank Measurement Angle" , "btatt.cycling_power_vector.flags.first_crank_measurement_angle" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_flags_crank_revolution_data , {
 "Crank Revolution Data" , "btatt.cycling_power_vector.flags.crank_revolution_data" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_crank_revolution_data_cumulative_crank_revolutions , {
 "cumulative_crank_revolutions" , "btatt.csc_measurement.cumulative_crank_revolutions" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_crank_revolution_data_last_crank_event_time , {
 "Last Crank Event Time" , "btatt.csc_measurement.last_crank_event_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_first_crank_measurement_angle , {
 "First Crank Measurement Angle" , "btatt.csc_measurement.first_crank_measurement_angle" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_instantaneous_force_magnitude_array , {
 "Instantaneous Force Magnitude Array" , "btatt.csc_measurement.instantaneous_force_magnitude_array" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_vector_instantaneous_torque_magnitude_array , {
 "Instantaneous Torque Magnitude Array" , "btatt.csc_measurement.instantaneous_torque_magnitude_array" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_opcode , {
 "Opcode" , "btatt.cycling_power_control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( cycling_power_control_point_opcode ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_cumulative_value , {
 "Cumulative Value" , "btatt.cycling_power_control_point.cumulative_value" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_sensor_location , {
 "Sensor Location" , "btatt.cycling_power_control_point.sensor_location" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_crank_length , {
 "Crank Length" , "btatt.cycling_power_control_point.crank_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_chain_length , {
 "Chain Length" , "btatt.cycling_power_control_point.chain_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_chain_weight , {
 "Chain Weight" , "btatt.cycling_power_control_point.chain_weight" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_span_length , {
 "Span Length" , "btatt.cycling_power_control_point.span_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask , {
 "Content Mask" , "btatt.cycling_power_control_point.content_mask" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_reserved , {
 "Reserved" , "btatt.cycling_power_control_point.content_mask.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_accumulated_energy , {
 "Accumulated Energy" , "btatt.cycling_power_control_point.content_mask.accumulated_energy" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x100 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_bottom_dead_spot_angle , {
 "Bottom Dead Spot Angle" , "btatt.cycling_power_control_point.content_mask.bottom_dead_spot_angle" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x080 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_top_dead_spot_angle , {
 "Top Dead Spot Angle" , "btatt.cycling_power_control_point.content_mask.top_dead_spot_angle" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x040 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_extreme_angles , {
 "Extreme Angles" , "btatt.cycling_power_control_point.content_mask.extreme_angles" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x020 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_extreme_magnitudes , {
 "Extreme Magnitudes" , "btatt.cycling_power_control_point.content_mask.extreme_magnitudes" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x010 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_crank_revolution_data , {
 "Crank Revolution Data" , "btatt.cycling_power_control_point.content_mask.crank_revolution_data" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x008 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_wheel_revolution_data , {
 "Wheel Revolution Data" , "btatt.cycling_power_control_point.content_mask.wheel_revolution_data" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x004 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_accumulated_torque , {
 "Accumulated Torque" , "btatt.cycling_power_control_point.content_mask.accumulated_torque" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x002 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_content_mask_pedal_power_balance , {
 "Pedal Power Balance" , "btatt.cycling_power_control_point.content_mask.pedal_power_balance" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x001 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_request_opcode , {
 "Request Opcode" , "btatt.cycling_power_control_point.request_opcode" , FT_UINT8 , BASE_HEX , VALS ( cycling_power_control_point_opcode ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_response_value , {
 "Response Value" , "btatt.cycling_power_control_point.response_value" , FT_UINT8 , BASE_HEX , VALS ( cycling_power_control_point_response_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_start_offset_compensation , {
 "Start Offset Compensation" , "btatt.cycling_power_control_point.start_offset_compensation" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_sampling_rate , {
 "Sampling Rate" , "btatt.cycling_power_control_point.sampling_rate" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cycling_power_control_point_factory_calibration_date , {
 "Factory Calibration Date" , "btatt.cycling_power_control_point.factory_calibration_date" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags , {
 "Flags" , "btatt.location_and_speed.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_reserved , {
 "Reserved" , "btatt.location_and_speed.flags.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xC000 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_heading_source , {
 "Heading Source" , "btatt.location_and_speed.flags.heading_source" , FT_BOOLEAN , 16 , TFS ( & flags_heading_source_tfs ) , 0x3000 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_elevation_source , {
 "Elevation Source" , "btatt.location_and_speed.flags.elevation_source" , FT_UINT16 , BASE_HEX , VALS ( location_and_speed_flags_elevation_source_vals ) , 0x0C00 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_speed_and_distance_format , {
 "Speed_and Distance Format" , "btatt.location_and_speed.flags.speed_and_distance_format" , FT_BOOLEAN , 16 , TFS ( & location_and_speed_flags_speed_and_distance_format_tfs ) , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_position_status , {
 "Position Status" , "btatt.location_and_speed.flags.position_status" , FT_UINT16 , BASE_HEX , VALS ( flags_position_status_vals ) , 0x0180 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_utc_time , {
 "UTC Time Present" , "btatt.location_and_speed.flags.utc_time" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_rolling_time , {
 "Rolling Time" , "btatt.location_and_speed.flags.rolling_time" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_heading , {
 "Heading" , "btatt.location_and_speed.flags.heading" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_elevation , {
 "Elevation" , "btatt.location_and_speed.flags.elevation" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_location , {
 "Location" , "btatt.location_and_speed.flags.location" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_total_distance , {
 "Total Distance Present" , "btatt.location_and_speed.flags.total_distance" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_flags_instantaneous_speed , {
 "Instantaneous Speed" , "btatt.location_and_speed.flags.instantaneous_speed" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_instantaneous_speed , {
 "Instantaneous Speed" , "btatt.location_and_speed.instantaneous_speed" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_total_distance , {
 "Total Distance" , "btatt.location_and_speed.total_distance" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_location_longitude , {
 "Location Longitude" , "btatt.location_and_speed.location.longitude" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_location_latitude , {
 "Location Latitude" , "btatt.location_and_speed.location.latitude" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_elevation , {
 "Elevation" , "btatt.location_and_speed.elevation" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_heading , {
 "Heading" , "btatt.location_and_speed.heading" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_rolling_time , {
 "Rolling Time" , "btatt.location_and_speed.rolling_time" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_location_and_speed_utc_time , {
 "UTC Time" , "btatt.location_and_speed.utc_time" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags , {
 "Flags" , "btatt.navigation.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_reserved , {
 "Reserved" , "btatt.navigation.flags.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFE00 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_destination_reached , {
 "Destination Reached" , "btatt.navigation.flags.destination_reached" , FT_BOOLEAN , 16 , NULL , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_waypoint_reached , {
 "Waypoint Reached" , "btatt.navigation.flags.waypoint_reached" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_navigation_indicator_type , {
 "Navigation Indicator Type" , "btatt.navigation.flags.navigation_indicator_type" , FT_BOOLEAN , 16 , TFS ( & navigation_indicator_type_tfs ) , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_heading_source , {
 "Heading Source" , "btatt.navigation.flags.heading_source" , FT_BOOLEAN , 16 , TFS ( & flags_heading_source_tfs ) , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_position_status , {
 "Position Status" , "btatt.navigation.flags.position_status" , FT_UINT16 , BASE_HEX , VALS ( flags_position_status_vals ) , 0x0018 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_estimated_time_of_arrival , {
 "Estimated Time of Arrival" , "btatt.navigation.flags.estimated_time_of_arrival" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_remaining_vertical_distance , {
 "Remaining Vertical Distance" , "btatt.navigation.flags.remaining_vertical_distance" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_flags_remaining_distance , {
 "Remaining Distance" , "btatt.navigation.flags.remaining_distance" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_bearing , {
 "Bearing" , "btatt.navigation.bearing" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_heading , {
 "Heading" , "btatt.navigation.heading" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_remaining_distance , {
 "Remaining Distance" , "btatt.navigation.remaining_distance" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_remaining_vertical_distance , {
 "Remaining Vertical Distance" , "btatt.navigation.remaining_vertical_distance" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_navigation_estimated_time_of_arrival , {
 "Estimated Time of Arrival" , "btatt.navigation.estimated_time_of_arrival" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags , {
 "Flags" , "btatt.position_quality.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_reserved , {
 "Reserved" , "btatt.position_quality.flags.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFE00 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_position_status , {
 "Position Status" , "btatt.position_quality.flags.position_status" , FT_UINT16 , BASE_HEX , VALS ( flags_position_status_vals ) , 0x0180 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_vdop , {
 "VDOP" , "btatt.position_quality.flags.vdop" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_hdop , {
 "HDOP" , "btatt.position_quality.flags.hdop" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_evpe , {
 "EVPE" , "btatt.position_quality.flags.evpe" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_ehpe , {
 "EHPE" , "btatt.position_quality.flags.ehpe" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_time_to_first_fix , {
 "Time to First Fix" , "btatt.position_quality.flags.time_to_first_fix" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_number_of_beacons_in_view , {
 "Number of Beacons in View" , "btatt.position_quality.flags.number_of_beacons_in_view" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_flags_number_of_beacons_in_solution , {
 "Number of Beacons_in Solution" , "btatt.position_quality.flags.number_of_beacons_in_solution" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_number_of_beacons_in_solution , {
 "number_of_beacons_in_solution" , "btatt.position_quality.number_of_beacons_in_solution" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_number_of_beacons_in_view , {
 "number_of_beacons_in_view" , "btatt.position_quality.number_of_beacons_in_view" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_time_to_first_fix , {
 "time_to_first_fix" , "btatt.position_quality.time_to_first_fix" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_ehpe , {
 "EHPE" , "btatt.position_quality.ehpe" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_evpe , {
 "EVPE" , "btatt.position_quality.evpe" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_hdop , {
 "HDOP" , "btatt.position_quality.hdop" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_position_quality_vdop , {
 "VDOP" , "btatt.position_quality.vdop" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_opcode , {
 "Opcode" , "btatt.ln_control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( ln_control_point_opcode ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_cumulative_value , {
 "Cumulative Value" , "btatt.ln_control_point.cumulative_value" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask , {
 "Content Mask" , "btatt.ln_control_point.content_mask" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_reserved , {
 "Reserved" , "btatt.ln_control_point.content_mask.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFF80 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_utc_time , {
 "UTC Time" , "btatt.ln_control_point.content_mask.utc_time" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_rolling_time , {
 "Rolling Time" , "btatt.ln_control_point.content_mask.rolling_time" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_heading , {
 "Heading" , "btatt.ln_control_point.content_mask.heading" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_elevation , {
 "Elevation" , "btatt.ln_control_point.content_mask.elevation" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_location , {
 "Location" , "btatt.ln_control_point.content_mask.location" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_total_distance , {
 "Total Distance" , "btatt.ln_control_point.content_mask.total_distance" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_content_mask_instantaneous_speed , {
 "Instantaneous Speed" , "btatt.ln_control_point.content_mask.instantaneous_speed" , FT_BOOLEAN , 16 , TFS ( & control_point_mask_value_tfs ) , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_navigation_control , {
 "Navigation Control" , "btatt.ln_control_point.navigation_control" , FT_UINT8 , BASE_HEX , VALS ( ln_control_point_navigation_control_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_route_number , {
 "Route Number" , "btatt.ln_control_point.route_number" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_fix_rate , {
 "Fix Rate" , "btatt.ln_control_point.fix_rate" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_elevation , {
 "Elevation" , "btatt.ln_control_point.elevation" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_request_opcode , {
 "Request Opcode" , "btatt.ln_control_point.request_opcode" , FT_UINT8 , BASE_HEX , VALS ( ln_control_point_opcode ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_response_value , {
 "Response Value" , "btatt.ln_control_point.response_value" , FT_UINT8 , BASE_HEX , VALS ( ln_control_point_response_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_response_value_number_of_routes , {
 "Number of Routes" , "btatt.ln_control_point.number_of_routes" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ln_control_point_response_value_name_of_route , {
 "Name_of Route" , "btatt.ln_control_point.name_of_route" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags , {
 "Flags" , "btatt.body_composition_measurement.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_reserved , {
 "Reserved" , "btatt.body_composition_measurement.flags.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xE000 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_multiple_packet_measurement , {
 "Multiple Packet Measurement" , "btatt.body_composition_measurement.flags.multiple_packet_measurement" , FT_BOOLEAN , 16 , NULL , 0x1000 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_height , {
 "Height" , "btatt.body_composition_measurement.flags.height" , FT_BOOLEAN , 16 , NULL , 0x0800 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_weight , {
 "Weight" , "btatt.body_composition_measurement.flags.weight" , FT_BOOLEAN , 16 , NULL , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_impedance , {
 "Impedance" , "btatt.body_composition_measurement.flags.impedance" , FT_BOOLEAN , 16 , NULL , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_body_water_mass , {
 "Body Water Mass" , "btatt.body_composition_measurement.flags.body_water_mass" , FT_BOOLEAN , 16 , NULL , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_soft_lean_mass , {
 "Soft Lean Mass" , "btatt.body_composition_measurement.flags.soft_lean_mass" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_fat_free_mass , {
 "Fat Free Mass" , "btatt.body_composition_measurement.flags.fat_free_mass" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_muscle_mass , {
 "Muscle Mass" , "btatt.body_composition_measurement.flags.muscle_mass" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_muscle_percentage , {
 "Muscle Percentage" , "btatt.body_composition_measurement.flags.muscle_percentage" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_basal_metabolism , {
 "Basal Metabolism" , "btatt.body_composition_measurement.flags.basal_metabolism" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_user_id , {
 "User ID" , "btatt.body_composition_measurement.flags.user_id" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_timestamp , {
 "Timestamp" , "btatt.body_composition_measurement.flags.timestamp" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_flags_measurement_units , {
 "Measurement Units" , "btatt.body_composition_measurement.flags.measurement_units" , FT_UINT16 , BASE_HEX , VALS ( body_composition_measurement_flags_measurement_units_vals ) , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_body_fat_percentage , {
 "Body Fat Percentage" , "btatt.body_composition_measurement.body_fat_percentage" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_timestamp , {
 "Timestamp" , "btatt.body_composition_measurement.timestamp" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_user_id , {
 "User ID" , "btatt.body_composition_measurement.user_id" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_basal_metabolism , {
 "Basal Metabolism" , "btatt.body_composition_measurement.basal_metabolism" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_muscle_percentage , {
 "Muscle Percentage" , "btatt.body_composition_measurement.muscle_percentage" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_muscle_mass_lb , {
 "Muscle Mass [lb]" , "btatt.body_composition_measurement.muscle_mass.lb" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_muscle_mass_kg , {
 "Muscle Mass [kg]" , "btatt.body_composition_measurement.muscle_mass.kg" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_fat_free_mass_lb , {
 "Fat Free Mass [lb]" , "btatt.body_composition_measurement.fat_free_mass.lb" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_fat_free_mass_kg , {
 "Fat Free Mass [kg]" , "btatt.body_composition_measurement.fat_free_mass.kg" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_soft_lean_mass_lb , {
 "Soft Lean Mass [lb]" , "btatt.body_composition_measurement.soft_lean_mass.lb" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_soft_lean_mass_kg , {
 "Soft Lean Mass [kg]" , "btatt.body_composition_measurement.soft_lean_mass.kg" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_body_water_mass_lb , {
 "Body Water Mass [lb]" , "btatt.body_composition_measurement.body_water_mass.lb" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_body_water_mass_kg , {
 "Body Water Mass [kg]" , "btatt.body_composition_measurement.body_water_mass.kg" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_impedance , {
 "Impedance" , "btatt.body_composition_measurement.impedance" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_weight_lb , {
 "Weight [lb]" , "btatt.body_composition_measurement.weight.lb" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_weight_kg , {
 "Weight [kg]" , "btatt.body_composition_measurement.weight.kg" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_height_inches , {
 "Height [inches]" , "btatt.body_composition_measurement.height.inches" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_body_composition_measurement_height_meter , {
 "Height [meter]" , "btatt.body_composition_measurement.height.meter" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_flags , {
 "Flags" , "btatt.weight_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_flags_reserved , {
 "Reserved" , "btatt.weight_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_flags_bmi_and_height , {
 "BMI and Height" , "btatt.weight_measurement.flags.bmi_and_height" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_flags_user_id , {
 "User ID" , "btatt.weight_measurement.flags.user_id" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_flags_timestamp , {
 "Timestamp" , "btatt.weight_measurement.flags.timestamp" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_flags_measurement_units , {
 "Measurement Units" , "btatt.weight_measurement.flags.measurement_units" , FT_BOOLEAN , 8 , TFS ( & weight_measurement_flags_measurement_units_tfs ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_weight_lb , {
 "Weight [lb]" , "btatt.weight_measurement.weight.lb" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_weight_kg , {
 "Weight [kg]" , "btatt.weight_measurement.weight.kg" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_timestamp , {
 "Timestamp" , "btatt.weight_measurement.timestamp" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_user_id , {
 "User ID" , "btatt.weight_measurement.user_id" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_bmi , {
 "BMI" , "btatt.weight_measurement.bmi" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_height_in , {
 "Height [in]" , "btatt.weight_measurement.height.in" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_weight_measurement_height_m , {
 "Height [m]" , "btatt.weight_measurement.height.m" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_user_control_point_opcode , {
 "Opcode" , "btatt.user_control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( user_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_user_control_point_request_opcode , {
 "Request Opcode" , "btatt.user_control_point.request_opcode" , FT_UINT8 , BASE_HEX , VALS ( user_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_user_control_point_response_value , {
 "Response Value" , "btatt.user_control_point.response_value" , FT_UINT8 , BASE_HEX , VALS ( user_control_point_response_value_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_user_control_point_consent_code , {
 "Consent Code" , "btatt.user_control_point.consent_code" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_size , {
 "Size" , "btatt.cgm_measurement.size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags , {
 "Flags" , "btatt.cgm_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags_cgm_trend_information , {
 "CGM Trend Information" , "btatt.cgm_measurement.flags.cgm_trend_information" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags_cgm_quality , {
 "CGM Quality" , "btatt.cgm_measurement.flags.cgm_quality" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags_reserved , {
 "Reserved" , "btatt.cgm_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0x38 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags_sensor_status_annunciation_warning , {
 "Sensor Status Annunciation - Warning" , "btatt.cgm_measurement.flags.sensor_status_annunciation.warning" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags_sensor_status_annunciation_cal_temp , {
 "Sensor Status Annunciation - Cal/Temp" , "btatt.cgm_measurement.flags.sensor_status_annunciation.cal_temp" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_flags_sensor_status_annunciation_status , {
 "Sensor Status Annunciation - Status" , "btatt.cgm_measurement.flags.sensor_status_annunciation.status" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_glucose_concentration , {
 "Glucose Concentration" , "btatt.cgm_measurement.glucose_concentration" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_time_offset , {
 "Time Offset" , "btatt.cgm_measurement.time_offset" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation , {
 "Sensor Status Annunciation" , "btatt.cgm.sensor_status_annunciation" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status , {
 "Status" , "btatt.cgm.sensor_status_annunciation.status" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_reserved , {
 "Reserved" , "btatt.cgm.sensor_status_annunciation.status.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_general_device_fault_has_occurred_in_the_sensor , {
 "General Device Fault has Occurred in the Sensor" , "btatt.cgm.sensor_status_annunciation.status.general_device_fault_has_occurred_in_the_sensor" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_device_specific_alert , {
 "Device Specific Alert" , "btatt.cgm.sensor_status_annunciation.status.device_specific_alert" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_sensor_malfunction , {
 "Sensor Malfunction" , "btatt.cgm.sensor_status_annunciation.status.sensor_malfunction" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_sensor_type_incorrect_for_device , {
 "Sensor Type Incorrect for Device" , "btatt.cgm.sensor_status_annunciation.status.sensor_type_incorrect_for_device" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_device_battery_low , {
 "Device Battery Low" , "btatt.cgm.sensor_status_annunciation.status.device_battery_low" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_status_session_stopped , {
 "Session Stopped" , "btatt.cgm.sensor_status_annunciation.status.session_stopped" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp , {
 "Cal/Temp" , "btatt.cgm.sensor_status_annunciation.cal_temp" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_reserved , {
 "Reserved" , "btatt.cgm.sensor_status_annunciation.cal_temp.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xC0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_sensor_temperature_too_low_for_valid_test_result_at_time_of_measurement , {
 "Sensor Temperature too Low for Valid Test Result at Time of Measurement" , "btatt.cgm.sensor_status_annunciation.cal_temp.sensor_temperature_too_low_for_valid_test_result_at_time_of_measurement" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_sensor_temperature_too_high_for_valid_test_result_at_time_of_measurement , {
 "Sensor Temperature too High for Valid Test Result at Time of Measurement" , "btatt.cgm_measurement.sensor_cal_temp_annunciation.cal_temp.sensor_temperature_too_high_for_valid_test_result_at_time_of_measurement" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_calibration_required , {
 "Calibration Required" , "btatt.cgm_measurement.sensor_cal_temp_annunciation.cal_temp.calibration_required" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_calibration_recommended , {
 "Calibration Recommended" , "btatt.cgm_measurement.sensor_cal_temp_annunciation.cal_temp.calibration_recommended" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_calibration_not_allowed , {
 "Calibration not Allowed" , "btatt.cgm_measurement.sensor_cal_temp_annunciation.cal_temp.calibration_not_allowed" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_cal_temp_time_synchronization_between_sensor_and_collector_required , {
 "Time Synchronization between Sensor and Collector Required" , "btatt.cgm_measurement.sensor_cal_temp_annunciation.cal_temp.time_synchronization_between_sensor_and_collector_required" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning , {
 "Warning" , "btatt.cgm.sensor_status_annunciation.warning" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_result_higher_than_the_device_can_process , {
 "Sensor Result Higher than the Device Can Process" , "btatt.cgm.sensor_status_annunciation.warning.sensor_result_higher_than_the_device_can_process" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_result_lower_than_the_device_can_process , {
 "Sensor Result Lower than the Device Can Process" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_result_lower_than_the_device_can_process" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_rate_of_increase_exceeded , {
 "Sensor Rate of Increase Exceeded" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_rate_of_increase_exceeded" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_rate_of_decrease_exceeded , {
 "Sensor Rate of Decrease Exceeded" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_rate_of_decrease_exceeded" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_result_higher_than_the_hyper_level , {
 "Sensor Result Higher than the Hyper Level" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_result_higher_than_the_hyper_level" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_result_lower_than_the_hypo_level , {
 "Sensor Result Lower than the Hypo Level" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_result_lower_than_the_hypo_level" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_result_higher_than_the_patient_high_level , {
 "Sensor Result Higher than the Patient High Level" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_result_higher_than_the_patient_high_level" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sensor_status_annunciation_warning_sensor_result_lower_than_the_patient_low_level , {
 "Sensor Result Lower than the Patient Low Level" , "btatt.cgm_measurement.sensor_warning_annunciation.warning.sensor_result_lower_than_the_patient_low_level" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_trend_information , {
 "Trend Information" , "btatt.cgm_measurement.trend_information" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_measurement_quality , {
 "Quality" , "btatt.cgm_measurement.quality" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_e2e_crc , {
 "E2E-CRC" , "btatt.cgm.e2e_crc" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature , {
 "Feature" , "btatt.cgm_feature.feature" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_reserved , {
 "Reserved" , "btatt.cgm_feature.feature.reserved" , FT_UINT24 , BASE_HEX , NULL , 0xFE0000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_quality , {
 "Quality" , "btatt.cgm_feature.feature.quality" , FT_BOOLEAN , 24 , NULL , 0x010000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_trend_information , {
 "Trend Information" , "btatt.cgm_feature.feature.trend_information" , FT_BOOLEAN , 24 , NULL , 0x008000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_multiple_sessions , {
 "Multiple Sessions" , "btatt.cgm_feature.feature.multiple_sessions" , FT_BOOLEAN , 24 , NULL , 0x004000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_multiple_bond , {
 "Multiple Bond" , "btatt.cgm_feature.feature.multiple_bond" , FT_BOOLEAN , 24 , NULL , 0x002000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_e2e_crc , {
 "E2E-CRC" , "btatt.cgm_feature.feature.e2e_crc" , FT_BOOLEAN , 24 , NULL , 0x001000 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_general_device_fault , {
 "General Device Fault" , "btatt.cgm_feature.feature.general_device_fault" , FT_BOOLEAN , 24 , NULL , 0x000800 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_sensor_type_error_detection , {
 "Sensor Type Error Detection" , "btatt.cgm_feature.feature.sensor_type_error_detection" , FT_BOOLEAN , 24 , NULL , 0x000400 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_low_battery_detection , {
 "Low Battery Detection" , "btatt.cgm_feature.feature.low_battery_detection" , FT_BOOLEAN , 24 , NULL , 0x000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_sensor_result_high_low_detection , {
 "Sensor Result High-Low Detection" , "btatt.cgm_feature.feature.sensor_result_high_low_detection" , FT_BOOLEAN , 24 , NULL , 0x000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_sensor_temperature_high_low_detection , {
 "Sensor Temperature High-Low Detection" , "btatt.cgm_feature.feature.sensor_temperature_high_low_detection" , FT_BOOLEAN , 24 , NULL , 0x000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_sensor_malfunction_detection , {
 "Sensor Malfunction Detection" , "btatt.cgm_feature.feature.sensor_malfunction_detection" , FT_BOOLEAN , 24 , NULL , 0x000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_device_specific_alert , {
 "Device Specific Alert" , "btatt.cgm_feature.feature.device_specific_alert" , FT_BOOLEAN , 24 , NULL , 0x000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_rate_of_increase_decrease_alerts , {
 "Rate of Increase Decrease Alerts" , "btatt.cgm_feature.feature.rate_of_increase_decrease_alerts" , FT_BOOLEAN , 24 , NULL , 0x000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_hyper_alerts , {
 "Hyper Alerts" , "btatt.cgm_feature.feature.hyper_alerts" , FT_BOOLEAN , 24 , NULL , 0x000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_hypo_alerts , {
 "Hypo Alerts" , "btatt.cgm_feature.feature.hypo_alerts" , FT_BOOLEAN , 24 , NULL , 0x000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_patient_high_low_alerts , {
 "Patient High-Low Alerts" , "btatt.cgm_feature.feature.patient_high_low_alerts" , FT_BOOLEAN , 24 , NULL , 0x000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_feature_feature_calibration , {
 "Calibration" , "btatt.cgm_feature.feature.calibration" , FT_BOOLEAN , 24 , NULL , 0x000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_type_and_sample_location , {
 "Type and Sample Location" , "btatt.cgm.type_and_sample_location" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_type , {
 "Type and Sample Location" , "btatt.cgm.type_and_sample_location.type" , FT_UINT8 , BASE_HEX , VALS ( cgm_feature_type_vals ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_sample_location , {
 "Sample Location" , "btatt.cgm.type_and_sample_location.sample_location" , FT_UINT8 , BASE_HEX , VALS ( cgm_feature_sample_location_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_time_offset , {
 "Time Offset" , "btatt.cgm.time_offset" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_status , {
 "Status" , "btatt.cgm.status" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_session_start_time , {
 "Session Start Time" , "btatt.cgm.session_start_time" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_session_run_time , {
 "Session Run Time" , "btatt.cgm.session_run_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_opcode , {
 "Opcode" , "btatt.cgm_specific_ops_control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( cgm_specific_ops_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_operand , {
 "Operand" , "btatt.cgm_specific_ops_control_point.operand" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_operand_communication_interval , {
 "Communication Interval" , "btatt.cgm_specific_ops_control_point.operand.communication_interval" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_glucose_concentration , {
 "Calibration Glucose Concentration" , "btatt.cgm_specific_ops_control_point.operand.calibration_glucose_concentration" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_time , {
 "Calibration Time" , "btatt.cgm_specific_ops_control_point.operand.calibration_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_next_calibration_time , {
 "Next Calibration Time" , "btatt.cgm_specific_ops_control_point.operand.next_calibration_time" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_data_record_number , {
 "Calibration Data Record Number" , "btatt.cgm_specific_ops_control_point.operand.calibration_data_record_number" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_status , {
 "Calibration Status" , "btatt.cgm_specific_ops_control_point.operand.calibration_status" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_status_reserved , {
 "Reserved" , "btatt.cgm_specific_ops_control_point.operand.calibration_status.reserved" , FT_UINT8 , BASE_DEC , NULL , 0xF8 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_status_pending , {
 "Pending" , "btatt.cgm_specific_ops_control_point.operand.calibration_status.pending" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_status_out_of_range , {
 "Out of Range" , "btatt.cgm_specific_ops_control_point.operand.calibration_status.out_of_range" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_calibration_status_rejected , {
 "Rejected" , "btatt.cgm_specific_ops_control_point.operand.calibration_status.rejected" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_operand_calibration_data_record_number , {
 "Calibration Data Record Number" , "btatt.cgm_specific_ops_control_point.operand.calibration_data_record_number" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_operand_alert_level , {
 "Alert Level [mg/dL]" , "btatt.cgm_specific_ops_control_point.operand.alert_level" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_operand_alert_level_rate , {
 "Alert Level Rate [mg/dL/min]" , "btatt.cgm_specific_ops_control_point.operand.alert_level_rate" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_request_opcode , {
 "Request Opcode" , "btatt.cgm_specific_ops_control_point.request_opcode" , FT_UINT8 , BASE_HEX , VALS ( cgm_specific_ops_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_cgm_specific_ops_control_point_response_code , {
 "Response Code" , "btatt.cgm_specific_ops_control_point.response_code" , FT_UINT8 , BASE_HEX , VALS ( cgm_specific_ops_control_point_response_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_uri , {
 "URI" , "btatt.uri" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_headers , {
 "HTTP Headers" , "btatt.http_headers" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_status_code , {
 "HTTP Status Code" , "btatt.http_status_code" , FT_UINT16 , BASE_DEC , VALS ( vals_http_status_code ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_data_status , {
 "HTTP Data Status" , "btatt.http_data_status" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_data_status_headers_received , {
 "Headers Received" , "btatt.http_data_status.headers_received" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_data_status_headers_truncated , {
 "Headers Truncated" , "btatt.http_data_status.headers_truncated" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_data_status_body_received , {
 "Body Received" , "btatt.http_data_status.body_received" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_data_status_body_truncated , {
 "Body Truncated" , "btatt.http_data_status.body_truncated" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_data_status_reserved , {
 "Reserved" , "btatt.http_data_status.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_entity_body , {
 "HTTP Entity Body" , "btatt.http_entity_body" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_http_control_point_opcode , {
 "Opcode" , "btatt.control_point.opcode" , FT_UINT8 , BASE_HEX , VALS ( http_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_https_security , {
 "HTTPS Security" , "btatt.https_security" , FT_UINT8 , BASE_HEX , VALS ( https_security_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_tds_opcode , {
 "Opcode" , "btatt.tds.opcode" , FT_UINT8 , BASE_HEX , VALS ( tds_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_tds_organization_id , {
 "Organization ID" , "btatt.tds.organization_id" , FT_UINT8 , BASE_HEX , VALS ( tds_organization_id_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_tds_result_code , {
 "Result Code" , "btatt.tds.result_code" , FT_UINT8 , BASE_HEX , VALS ( tds_result_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_tds_data , {
 "Data" , "btatt.tds.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp , {
 "OACP Features" , "btatt.ots.oacp" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_reserved , {
 "Reserved" , "btatt.ots.oacp.reserved" , FT_BOOLEAN , 32 , NULL , 0xFFFFFC00 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_abort , {
 "Abort" , "btatt.ots.oacp.abort" , FT_BOOLEAN , 32 , NULL , 0x00000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_patching_of_object , {
 "Patching of Object" , "btatt.ots.oacp.patching_of_object" , FT_BOOLEAN , 32 , NULL , 0x00000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_truncation_of_objects , {
 "Truncation of Objects" , "btatt.ots.oacp.truncation_of_objects" , FT_BOOLEAN , 32 , NULL , 0x00000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_appending_additional_data_to_object , {
 "Appending Additional Data to Object" , "btatt.ots.oacp.appending_additional_data_to_object" , FT_BOOLEAN , 32 , NULL , 0x00000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_write , {
 "Write" , "btatt.ots.oacp.write" , FT_BOOLEAN , 32 , NULL , 0x00000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_read , {
 "Read" , "btatt.ots.oacp.read" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_execute , {
 "Execute" , "btatt.ots.oacp.execute" , FT_BOOLEAN , 32 , NULL , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_calculate_checksum , {
 "Calculate Checksum" , "btatt.ots.oacp.calculate_checksum" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_delete , {
 "Delete" , "btatt.ots.oacp.delete" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_oacp_create , {
 "Create" , "btatt.ots.oacp.create" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_olcp , {
 "OLCP Features" , "btatt.ots.olcp" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_olcp_reserved , {
 "Reserved" , "btatt.ots.olcp.reserved" , FT_BOOLEAN , 32 , NULL , 0xFFFFFFF0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_olcp_clear_marking , {
 "Clear Marking" , "btatt.ots.olcp.clear_marking" , FT_BOOLEAN , 32 , NULL , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_olcp_request_number_of_objects , {
 "Request Number of Objects" , "btatt.ots.olcp.request_number_of_objects" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_olcp_order , {
 "Order" , "btatt.ots.olcp.order" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_feature_olcp_go_to , {
 "Go To" , "btatt.ots.olcp.go_to" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_object_name , {
 "Object Name" , "btatt.ots.object_name" , FT_STRING , STR_UNICODE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_current_size , {
 "Current Size" , "btatt.ots.current_size" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_allocated_size , {
 "Allocated Size" , "btatt.ots.allocated_size" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_object_id , {
 "Object ID" , "btatt.ots.object_id" , FT_UINT48 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties , {
 "Properties" , "btatt.ots.properties" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_reserved , {
 "Reserved" , "btatt.ots.properties.reserved" , FT_BOOLEAN , 32 , NULL , 0xFFFFFF00 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_mark , {
 "Mark" , "btatt.ots.properties.mark" , FT_BOOLEAN , 32 , NULL , 0x00000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_patch , {
 "Patch" , "btatt.ots.properties.patch" , FT_BOOLEAN , 32 , NULL , 0x00000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_truncate , {
 "Truncate" , "btatt.ots.properties.truncate" , FT_BOOLEAN , 32 , NULL , 0x00000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_append , {
 "Append" , "btatt.ots.properties.append" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_write , {
 "Write" , "btatt.ots.properties.write" , FT_BOOLEAN , 32 , NULL , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_read , {
 "Read" , "btatt.ots.properties.read" , FT_BOOLEAN , 32 , NULL , 0x00000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_execute , {
 "Execute" , "btatt.ots.properties.execute" , FT_BOOLEAN , 32 , NULL , 0x00000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_properties_delete , {
 "Delete" , "btatt.ots.properties.delete" , FT_BOOLEAN , 32 , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags , {
 "Properties" , "btatt.ots.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags_reserved , {
 "Reserved" , "btatt.ots.flags.reserved" , FT_BOOLEAN , 8 , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags_object_deletion , {
 "Object Deletion" , "btatt.ots.flags.object_deletion" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags_object_creation , {
 "Object Creation" , "btatt.ots.flags.object_creation" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags_change_occurred_to_the_object_metadata , {
 "Change Occurred to the Object Metadata" , "btatt.ots.flags.change_occurred_to_the_object_metadata" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags_change_occurred_to_the_object_contents , {
 "Change Occurred to the Object Contents" , "btatt.ots.flags.change_occurred_to_the_object_contents" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_flags_source_of_change , {
 "Source of Change" , "btatt.ots.flags.source_of_change" , FT_BOOLEAN , 8 , TFS ( & tfs_client_server ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_action_opcode , {
 "Opcode" , "btatt.ots.action.opcode" , FT_UINT8 , BASE_HEX , VALS ( ots_action_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_size , {
 "Size" , "btatt.ots.size" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_offset , {
 "Offset" , "btatt.ots.offset" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_length , {
 "Length" , "btatt.ots.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_execute_data , {
 "Execute Data" , "btatt.ots.execute_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_action_response_opcode , {
 "Response Opcode" , "btatt.ots.action.response_opcode" , FT_UINT8 , BASE_HEX , VALS ( ots_action_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_action_result_code , {
 "Result Code" , "btatt.ots.action.result_code" , FT_UINT8 , BASE_HEX , VALS ( ots_action_result_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_checksum , {
 "Checksum" , "btatt.ots.checksum" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_list_opcode , {
 "Opcode" , "btatt.ots.list.opcode" , FT_UINT8 , BASE_HEX , VALS ( ots_list_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_list_order , {
 "Order" , "btatt.ots.list.order" , FT_UINT8 , BASE_HEX , VALS ( ots_list_order_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_list_response_opcode , {
 "Response Opcode" , "btatt.ots.list.response_opcode" , FT_UINT8 , BASE_HEX , VALS ( ots_list_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_list_result_code , {
 "Result Code" , "btatt.ots.list.result_code" , FT_UINT8 , BASE_HEX , VALS ( ots_list_result_code_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_list_total_number_of_objects , {
 "Total Number of Objects" , "btatt.ots.list.total_number_of_objects" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_filter , {
 "Filter" , "btatt.ots.filter" , FT_UINT8 , BASE_HEX , VALS ( ots_filter_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_size_from , {
 "Size From" , "btatt.ots.size_from" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_size_to , {
 "Size To" , "btatt.ots.size_to" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_name_string , {
 "Name String" , "btatt.ots.name_string" , FT_STRING , STR_UNICODE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_object_first_created , {
 "First Created" , "btatt.ots.first_created" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_ots_object_last_modified , {
 "Last Modified" , "btatt.ots.last_modified" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags , {
 "Flags" , "btatt.plxs.spot_check_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags_reserved , {
 "Reserved" , "btatt.plxs.spot_check_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags_device_clock_is_not_set , {
 "Device Clock is not Set" , "btatt.plxs.spot_check_measurement.flags.device_clock_is_not_set" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags_pulse_amplitude_index , {
 "Pulse Amplitude Index" , "btatt.plxs.spot_check_measurement.flags.pulse_amplitude_index" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags_device_and_sensor_status , {
 "Device and Sensor Status" , "btatt.plxs.spot_check_measurement.flags.device_and_sensor_status" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags_measurement_status , {
 "Measurement Status" , "btatt.plxs.spot_check_measurement.flags.measurement_status" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_flags_timestamp , {
 "Timestamp" , "btatt.plxs.spot_check_measurement.flags.timestamp" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spo2 , {
 "SpO2" , "btatt.plxs.spot_check_measurement.spo2" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_pulse_rate , {
 "Pulse Rate" , "btatt.plxs.spot_check_measurement.pulse_rate" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spot_check_measurement_timestamp , {
 "Timestamp" , "btatt.plxs.spot_check_measurement.timestamp" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status , {
 "Timestamp" , "btatt.plxs.spot_check_measurement.measurement_status" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_invalid_measurement_detected , {
 "Invalid Measurement Detected" , "btatt.plxs.spot_check_measurement.measurement_status.invalid_measurement_detected" , FT_BOOLEAN , 16 , NULL , 0x8000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_questionable_measurement_detected , {
 "Questionable Measurement Detected" , "btatt.plxs.spot_check_measurement.measurement_status.questionable_measurement_detected" , FT_BOOLEAN , 16 , NULL , 0x4000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_measurement_unavailable , {
 "Measurement Unavailable" , "btatt.plxs.spot_check_measurement.measurement_status.measurement_unavailable" , FT_BOOLEAN , 16 , NULL , 0x2000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_calibration_ongoing , {
 "Calibration Ongoing" , "btatt.plxs.spot_check_measurement.measurement_status.calibration_ongoing" , FT_BOOLEAN , 16 , NULL , 0x1000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_data_for_testing , {
 "Data for Testing" , "btatt.plxs.spot_check_measurement.measurement_status.data_for_testing" , FT_BOOLEAN , 16 , NULL , 0x0800 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_data_for_demonstration , {
 "Data for Demonstration" , "btatt.plxs.spot_check_measurement.measurement_status.data_for_demonstration" , FT_BOOLEAN , 16 , NULL , 0x0400 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_data_from_measurement_storage , {
 "Data from Measurement Storage" , "btatt.plxs.spot_check_measurement.measurement_status.data_from_measurement_storage" , FT_BOOLEAN , 16 , NULL , 0x0200 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_fully_qualified_data , {
 "Fully Qualified Data" , "btatt.plxs.spot_check_measurement.measurement_status.fully_qualified_data" , FT_BOOLEAN , 16 , NULL , 0x0100 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_validated_data , {
 "Validated Data" , "btatt.plxs.spot_check_measurement.measurement_status.validated_data" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_early_estimated_data , {
 "Early Estimated Data" , "btatt.plxs.spot_check_measurement.measurement_status.early_estimated_data" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_measurement_ongoing , {
 "Measurement Ongoing" , "btatt.plxs.spot_check_measurement.measurement_status.measurement_ongoing" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_measurement_status_reserved , {
 "Reserved" , "btatt.plxs.spot_check_measurement.measurement_status.reserved" , FT_BOOLEAN , 16 , NULL , 0x001F , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status , {
 "Device and Sensor Status" , "btatt.plxs.spot_check_measurement.device_and_sensor_status" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_reserved , {
 "Reserved" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.reserved" , FT_UINT24 , BASE_HEX , NULL , 0xFF0000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_sensor_disconnected , {
 "Sensor Disconnected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.sensor_disconnected" , FT_BOOLEAN , 24 , NULL , 0x008000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_sensor_malfunctioning , {
 "Sensor Malfunctioning" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.sensor_malfunctioning" , FT_BOOLEAN , 24 , NULL , 0x004000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_sensor_displaced , {
 "Sensor Displaced" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.sensor_displaced" , FT_BOOLEAN , 24 , NULL , 0x002000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_unknown_sensor_connected , {
 "Unknown Sensor Connected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.unknown_sensor_connected" , FT_BOOLEAN , 24 , NULL , 0x001000 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_sensor_unconnected_to_user , {
 "Unconnected to User" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.unconnected_to_user" , FT_BOOLEAN , 24 , NULL , 0x000800 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_sensor_interference_detected , {
 "Interference Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.interference_detected" , FT_BOOLEAN , 24 , NULL , 0x000400 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_signal_analysis_ongoing , {
 "Signal Analysis Ongoing" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.signal_analysis_ongoing" , FT_BOOLEAN , 24 , NULL , 0x000200 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_questionable_pulse_detected , {
 "Questionable Pulse Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.questionable_pulse_detected" , FT_BOOLEAN , 24 , NULL , 0x000100 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_non_pulsatile_signal_detected , {
 "Non Pulsatile Signal Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.non_pulsatile_signal_detected" , FT_BOOLEAN , 24 , NULL , 0x000080 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_erratic_signal_detected , {
 "Erratic Signal Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.erratic_signal_detected" , FT_BOOLEAN , 24 , NULL , 0x000040 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_low_perfusion_detected , {
 "Low Perfusion Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.low_perfusion_detected" , FT_BOOLEAN , 24 , NULL , 0x000020 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_poor_signal_detected , {
 "Poor Signal Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.poor_signal_detected" , FT_BOOLEAN , 24 , NULL , 0x000010 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_inadequate_signal_detected , {
 "Inadequate Signal Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.inadequate_signal_detected" , FT_BOOLEAN , 24 , NULL , 0x000008 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_signal_processing_irregularity_detected , {
 "Signal Processing Irregularity Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.signal_processing_irregularity_detected" , FT_BOOLEAN , 24 , NULL , 0x000004 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_equipment_malfunction_detected , {
 "Equipment Malfunction Detected" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.equipment_malfunction_detected" , FT_BOOLEAN , 24 , NULL , 0x000002 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_device_and_sensor_status_extended_display_update_ongoing , {
 "Extended Display Update Ongoing" , "btatt.plxs.spot_check_measurement.device_and_sensor_status.extended_display_update_ongoing" , FT_BOOLEAN , 24 , NULL , 0x000001 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_pulse_amplitude_index , {
 "Pulse Amplitude Index" , "btatt.plxs.spot_check_measurement.pulse_amplitude_index" , FT_IEEE_11073_SFLOAT , BASE_FLOAT , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spo2pr_spot_check , {
 "SpO2PR Spot Check" , "btatt.plxs.spo2pr_spot_check" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spo2pr_normal , {
 "SpO2PR Normal" , "btatt.plxs.spo2pr_normal" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spo2pr_fast , {
 "SpO2PR Fast" , "btatt.plxs.spo2pr_fast" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_spo2pr_slow , {
 "SpO2PR Slow" , "btatt.plxs.spo2pr_slow" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags , {
 "Flags" , "btatt.plxs.continuous_measurement.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags_reserved , {
 "Reserved" , "btatt.plxs.continuous_measurement.flags.reserved" , FT_UINT8 , BASE_HEX , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags_pulse_amplitude_index , {
 "Pulse Amplitude Index" , "btatt.plxs.continuous_measurement.flags.pulse_amplitude_index" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags_device_and_sensor_status , {
 "Device and Sensor Status" , "btatt.plxs.continuous_measurement.flags.device_and_sensor_status" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags_measurement_status , {
 "Measurement Status" , "btatt.plxs.continuous_measurement.flags.measurement_status" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags_spo2pr_slow , {
 "SpO2PR-Slow" , "btatt.plxs.continuous_measurement.flags.spo2pr_slow" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_continuous_measurement_flags_spo2pr_fast , {
 "SpO2PR-Fast" , "btatt.plxs.continuous_measurement.flags.spo2pr_fast" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features , {
 "Supported Features" , "btatt.plxs.features.supported_features" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_reserved , {
 "Reserved" , "btatt.plxs.features.supported_features.reserved" , FT_UINT16 , BASE_HEX , NULL , 0xFF00 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_multiple_bonds , {
 "Multiple Bonds" , "btatt.plxs.features.supported_features.multiple_bonds" , FT_BOOLEAN , 16 , NULL , 0x0080 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_pulse_amplitude_index , {
 "Pulse Amplitude Index" , "btatt.plxs.features.supported_features.pulse_amplitude_index" , FT_BOOLEAN , 16 , NULL , 0x0040 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_spo2pr_slow , {
 "SpO2PR-Slow" , "btatt.plxs.features.supported_features.spo2pr_slow" , FT_BOOLEAN , 16 , NULL , 0x0020 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_spo2pr_fast , {
 "SpO2PR-Fast" , "btatt.plxs.features.supported_features.spo2pr_fast" , FT_BOOLEAN , 16 , NULL , 0x0010 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_timestamp_storage_for_spot_check , {
 "Timestamp Storage for Spot-Check" , "btatt.plxs.features.supported_features.timestamp_storage_for_spot_check" , FT_BOOLEAN , 16 , NULL , 0x0008 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_measurement_storage_for_spot_check , {
 "Measurement Storage for Spot-Check" , "btatt.plxs.features.supported_features.measurement_storage_for_spot_check" , FT_BOOLEAN , 16 , NULL , 0x0004 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_device_and_sensor_status , {
 "Device and Sensor Status" , "btatt.plxs.features.supported_features.device_and_sensor_status" , FT_BOOLEAN , 16 , NULL , 0x0002 , NULL , HFILL }
 }
 , {
 & hf_btatt_plx_features_supported_features_measurement_status , {
 "Measurement Status" , "btatt.plxs.features.supported_features.measurement_status" , FT_BOOLEAN , 16 , NULL , 0x0001 , NULL , HFILL }
 }
 , {
 & hf_btatt_valid_range_lower_inclusive_value , {
 "Lower Inclusive Value" , "btatt.valid_range.lower_inclusive_value" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_valid_range_upper_inclusive_value , {
 "Upper Inclusive Value" , "btatt.valid_range.upper_inclusive_value" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_count , {
 "Count" , "btatt.regulatory_certification_data_list.count" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_length , {
 "Length" , "btatt.regulatory_certification_data_list.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item , {
 "Item" , "btatt.regulatory_certification_data_list.item" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_body , {
 "Authorizing Body" , "btatt.regulatory_certification_data_list.item.authorization_body" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_body_structure_type , {
 "Authorizing Body Structure Type" , "btatt.regulatory_certification_data_list.item.authorization_body_structure_type" , FT_UINT8 , BASE_DEC , VALS ( regulatory_certification_data_list_item_body_structure_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_body_structure_length , {
 "Authorizing Body Structure Length" , "btatt.regulatory_certification_data_list.item.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data , {
 "Authorizing Body Data" , "btatt.regulatory_certification_data_list.item.authorizing_body_data" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data_major_ig_version , {
 "Major IG Version" , "btatt.regulatory_certification_data_list.item.authorizing_body_data.major_ig_version" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data_minor_ig_version , {
 "Minor IG Version" , "btatt.regulatory_certification_data_list.item.authorizing_body_data.minor_ig_version" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data_certification_data_list_count , {
 "Certification Data List LCount" , "btatt.regulatory_certification_data_list.item.certified_device_class_list.count" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data_certification_data_list_length , {
 "Certification Data List Length" , "btatt.regulatory_certification_data_list.item.certified_device_class_list.length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data_certification_data_list , {
 "Certification Data List" , "btatt.regulatory_certification_data_list.item.certified_device_class_list" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_authorizing_body_data_certified_device_class , {
 "Certified Device Class" , "btatt.regulatory_certification_data_list.item.certified_device_class_list.entry" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_regulation_bit_field_type , {
 "Regulation Bit Field Type" , "btatt.regulatory_certification_data_list.item.regulation_bit_field_type" , FT_UINT16 , BASE_HEX , NULL , 0xFFFF , NULL , HFILL }
 }
 , {
 & hf_btatt_regulatory_certification_data_list_item_data , {
 "Data" , "btatt.regulatory_certification_data_list.item.data" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_timezone_information , {
 "Timezone Information" , "btatt.timezone_information" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btatt_timezone_information_information , {
 "Information" , "btatt.timezone_information.information" , FT_UINT8 , BASE_DEC , VALS ( timezone_information_vals ) , 0x7F , NULL , HFILL }
 }
 , {
 & hf_btatt_timezone_information_information_type , {
 "Type" , "btatt.timezone_information.information_type" , FT_BOOLEAN , 8 , TFS ( & timezone_information_type_tfs ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_request_in_frame , {
 "Request in Frame" , "btatt.request_in_frame" , FT_FRAMENUM , BASE_NONE , FRAMENUM_TYPE ( FT_FRAMENUM_REQUEST ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_response_in_frame , {
 "Response in Frame" , "btatt.response_in_frame" , FT_FRAMENUM , BASE_NONE , FRAMENUM_TYPE ( FT_FRAMENUM_RESPONSE ) , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_btatt , & ett_btatt_list , & ett_btatt_value , & ett_btatt_opcode , & ett_btatt_handle , & ett_btatt_characteristic_properties }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_btatt_uuid_format_unknown , {
 "btatt.uuid_format.unknown" , PI_PROTOCOL , PI_WARN , "Unknown format" , EXPFILL }
 }
 , {
 & ei_btatt_handle_too_few , {
 "btatt.handle.too_few" , PI_PROTOCOL , PI_WARN , "Too few handles, should be 2 or more" , EXPFILL }
 }
 , {
 & ei_btatt_mtu_exceeded , {
 "btatt.mtu.exceeded" , PI_PROTOCOL , PI_WARN , "Packet size exceed current ATT_MTU" , EXPFILL }
 }
 , {
 & ei_btatt_mtu_full , {
 "btatt.mtu.full" , PI_PROTOCOL , PI_NOTE , "Reached ATT_MTU. Attribute value may be longer." , EXPFILL }
 }
 , {
 & ei_btatt_consent_out_of_bounds , {
 "btatt.consent.out_of_bounds" , PI_PROTOCOL , PI_WARN , "Consent Code is out of bounds (0 to 9999)" , EXPFILL }
 }
 , {
 & ei_btatt_cgm_size_too_small , {
 "btatt.cgm_measurement.size.too_small" , PI_PROTOCOL , PI_WARN , "Size too small (6 or geater)" , EXPFILL }
 }
 , {
 & ei_btatt_opcode_invalid_request , {
 "btatt.opcode.invalid_request" , PI_PROTOCOL , PI_WARN , "Invalid request" , EXPFILL }
 }
 , {
 & ei_btatt_opcode_invalid_response , {
 "btatt.opcode.invalid_response" , PI_PROTOCOL , PI_WARN , "Invalid response" , EXPFILL }
 }
 , {
 & ei_btatt_invalid_usage , {
 "btatt.invalid_usage" , PI_PROTOCOL , PI_WARN , "Invalid usage of this characteristic with this opcode" , EXPFILL }
 }
 , {
 & ei_btatt_invalid_length , {
 "btatt.invalid_length" , PI_PROTOCOL , PI_WARN , "Invalid length" , EXPFILL }
 }
 , {
 & ei_btatt_bad_data , {
 "btatt.bad_data" , PI_PROTOCOL , PI_WARN , "Bad Data" , EXPFILL }
 }
 , {
 & ei_btatt_unexpected_data , {
 "btatt.unexpected_data" , PI_PROTOCOL , PI_WARN , "Unexpected Data" , EXPFILL }
 }
 , {
 & ei_btatt_undecoded , {
 "btatt.undecoded" , PI_UNDECODED , PI_NOTE , "Undecoded" , EXPFILL }
 }
 , }
 ;
 static build_valid_func btatt_handle_da_build_value [ 1 ] = {
 btatt_handle_value }
 ;
 static decode_as_value_t btatt_handle_da_values = {
 btatt_handle_prompt , 1 , btatt_handle_da_build_value }
 ;
 static decode_as_t btatt_handle_da = {
 "btatt" , "ATT Handle" , "btatt.handle" , 1 , 0 , & btatt_handle_da_values , NULL , NULL , decode_as_default_populate_list , decode_as_default_reset , decode_as_default_change , NULL }
 ;
 proto_btatt = proto_register_protocol ( "Bluetooth Attribute Protocol" , "BT ATT" , "btatt" ) ;
 btatt_handle = register_dissector ( "btatt" , dissect_btatt , proto_btatt ) ;
 att_handle_dissector_table = register_dissector_table ( "btatt.handle" , "BT ATT Handle" , proto_btatt , FT_UINT16 , BASE_HEX ) ;
 proto_register_field_array ( proto_btatt , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_btatt = expert_register_protocol ( proto_btatt ) ;
 expert_register_field_array ( expert_btatt , ei , array_length ( ei ) ) ;
 mtus = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 requests = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 fragments = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 handle_to_uuid = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 module = prefs_register_protocol_subtree ( "Bluetooth" , proto_btatt , NULL ) ;
 prefs_register_static_text_preference ( module , "att.version" , "Bluetooth Protocol ATT version from Core 4.0" , "Version of protocol supported by this dissector." ) ;
 register_decode_as ( & btatt_handle_da ) ;
 }