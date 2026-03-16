void proto_register_btgatt ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_gatt_nordic_uart_tx , {
 "UART Tx" , "btgatt.nordic.uart_tx" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_uart_rx , {
 "UART Rx" , "btgatt.nordic.uart_rx" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_packet , {
 "Packet" , "btgatt.nordic.dfu.packet" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_opcode , {
 "Opcode" , "btgatt.nordic.dfu.control_point.opcode" , FT_UINT8 , BASE_DEC , VALS ( nordic_dfu_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_init_packet , {
 "Init Packet" , "btgatt.nordic.dfu.control_point.init_packet" , FT_UINT8 , BASE_HEX , VALS ( nordic_dfu_control_point_init_packet_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_image_type , {
 "Image Type" , "btgatt.nordic.dfu.control_point.image_type" , FT_UINT8 , BASE_HEX , VALS ( nordic_dfu_control_point_image_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_number_of_bytes , {
 "Number of Bytes of Firmware Image Received" , "btgatt.nordic.dfu.control_point.number_of_bytes" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_number_of_packets , {
 "Number of Packets" , "btgatt.nordic.dfu.control_point.number_of_packets" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_request_opcode , {
 "Request Opcode" , "btgatt.nordic.dfu.control_point.request_opcode" , FT_UINT8 , BASE_DEC , VALS ( nordic_dfu_control_point_opcode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_nordic_dfu_control_point_response_value , {
 "Response Value" , "btgatt.nordic.dfu.control_point.response_value" , FT_UINT8 , BASE_DEC , VALS ( nordic_dfu_control_point_response_value_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_accelerometer_data , {
 "Accelerometer Data" , "btgatt.microbit.accelerometer.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_accelerometer_x , {
 "X axis" , "btgatt.microbit.accelerometer.x" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "Accelerometer X axis" , HFILL }
 }
 , {
 & hf_gatt_microbit_accelerometer_y , {
 "Y axis" , "btgatt.microbit.accelerometer.y" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "Accelerometer Y axis" , HFILL }
 }
 , {
 & hf_gatt_microbit_accelerometer_z , {
 "Z axis" , "btgatt.microbit.accelerometer.z" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "Accelerometer Z axis" , HFILL }
 }
 , {
 & hf_gatt_microbit_accelerometer_period , {
 "Accelerometer Period" , "btgatt.microbit.accelerometer.period" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_milliseconds , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_magnetometer_data , {
 "Magnetometer Data" , "btgatt.microbit.magnetometer.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_magnetometer_x , {
 "X axis" , "btgatt.microbit.magnetometer.x" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "Magnetometer X axis" , HFILL }
 }
 , {
 & hf_gatt_microbit_magnetometer_y , {
 "Y axis" , "btgatt.microbit.magnetometer.y" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "Magnetometer Y axis" , HFILL }
 }
 , {
 & hf_gatt_microbit_magnetometer_z , {
 "Z axis" , "btgatt.microbit.magnetometer.z" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , "Magnetometer Z axis" , HFILL }
 }
 , {
 & hf_gatt_microbit_magnetometer_period , {
 "Magnetometer Period" , "btgatt.microbit.magnetometer.period" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_milliseconds , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_magnetometer_bearing , {
 "Magnetometer Bearing" , "btgatt.microbit.magnetometer.bearing" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_degree_bearing , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_button_a_state , {
 "Button A" , "btgatt.microbit.button.a" , FT_UINT8 , BASE_DEC , VALS ( btgatt_microbit_button_state_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_button_b_state , {
 "Button B" , "btgatt.microbit.button.b" , FT_UINT8 , BASE_DEC , VALS ( btgatt_microbit_button_state_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_pin_data , {
 "Pin Data" , "btgatt.microbit.pin_data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_pin_number , {
 "Pin Number" , "btgatt.microbit.pin_data.number" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_pin_value , {
 "Pin Value" , "btgatt.microbit.pin_data.value" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_pin_ad_config , {
 "Pin AD Configuration" , "btgatt.microbit.pin_ad_config.value" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin0 , {
 "Pin 0" , "btgatt.microbit.pin_ad_config.pin0" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000001 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin1 , {
 "Pin 1" , "btgatt.microbit.pin_ad_config.pin1" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000002 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin2 , {
 "Pin 2" , "btgatt.microbit.pin_ad_config.pin2" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000004 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin3 , {
 "Pin 3" , "btgatt.microbit.pin_ad_config.pin3" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000008 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin4 , {
 "Pin 4" , "btgatt.microbit.pin_ad_config.pin4" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000010 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin5 , {
 "Pin 5" , "btgatt.microbit.pin_ad_config.pin5" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000020 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin6 , {
 "Pin 6" , "btgatt.microbit.pin_ad_config.pin6" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000040 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin7 , {
 "Pin 7" , "btgatt.microbit.pin_ad_config.pin7" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000080 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin8 , {
 "Pin 8" , "btgatt.microbit.pin_ad_config.pin8" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000100 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin9 , {
 "Pin 9" , "btgatt.microbit.pin_ad_config.pin9" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000200 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin10 , {
 "Pin 10" , "btgatt.microbit.pin_ad_config.pin10" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000400 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin11 , {
 "Pin 11" , "btgatt.microbit.pin_ad_config.pin11" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x000800 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin12 , {
 "Pin 12" , "btgatt.microbit.pin_ad_config.pin12" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x001000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin13 , {
 "Pin 13" , "btgatt.microbit.pin_ad_config.pin13" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x002000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin14 , {
 "Pin 14" , "btgatt.microbit.pin_ad_config.pin14" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x004000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin15 , {
 "Pin 15" , "btgatt.microbit.pin_ad_config.pin15" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x008000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin16 , {
 "Pin 16" , "btgatt.microbit.pin_ad_config.pin16" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x010000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin17 , {
 "Pin 17" , "btgatt.microbit.pin_ad_config.pin17" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x020000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin18 , {
 "Pin 18" , "btgatt.microbit.pin_ad_config.pin18" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x040000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_ad_pin19 , {
 "Pin 19" , "btgatt.microbit.pin_ad_config.pin19" , FT_BOOLEAN , 20 , TFS ( & microbit_ad_tfs ) , 0x080000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_pin_io_config , {
 "Pin IO Configuration" , "btgatt.microbit.pin_io_config.value" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin0 , {
 "Pin 0" , "btgatt.microbit.pin_io_config.pin0" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000001 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin1 , {
 "Pin 1" , "btgatt.microbit.pin_io_config.pin1" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000002 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin2 , {
 "Pin 2" , "btgatt.microbit.pin_io_config.pin2" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000004 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin3 , {
 "Pin 3" , "btgatt.microbit.pin_io_config.pin3" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000008 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin4 , {
 "Pin 4" , "btgatt.microbit.pin_io_config.pin4" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000010 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin5 , {
 "Pin 5" , "btgatt.microbit.pin_io_config.pin5" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000020 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin6 , {
 "Pin 6" , "btgatt.microbit.pin_io_config.pin6" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000040 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin7 , {
 "Pin 7" , "btgatt.microbit.pin_io_config.pin7" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000080 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin8 , {
 "Pin 8" , "btgatt.microbit.pin_io_config.pin8" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000100 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin9 , {
 "Pin 9" , "btgatt.microbit.pin_io_config.pin9" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000200 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin10 , {
 "Pin 10" , "btgatt.microbit.pin_io_config.pin10" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000400 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin11 , {
 "Pin 11" , "btgatt.microbit.pin_io_config.pin11" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x000800 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin12 , {
 "Pin 12" , "btgatt.microbit.pin_io_config.pin12" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x001000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin13 , {
 "Pin 13" , "btgatt.microbit.pin_io_config.pin13" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x002000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin14 , {
 "Pin 14" , "btgatt.microbit.pin_io_config.pin14" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x004000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin15 , {
 "Pin 15" , "btgatt.microbit.pin_io_config.pin15" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x008000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin16 , {
 "Pin 16" , "btgatt.microbit.pin_io_config.pin16" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x010000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin17 , {
 "Pin 17" , "btgatt.microbit.pin_io_config.pin17" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x020000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin18 , {
 "Pin 18" , "btgatt.microbit.pin_io_config.pin18" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x040000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_io_pin19 , {
 "Pin 19" , "btgatt.microbit.pin_io_config.pin19" , FT_BOOLEAN , 20 , TFS ( & microbit_io_tfs ) , 0x080000 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_pwm_control , {
 "PWM Control" , "btgatt.microbit.pwm_control" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_led_matrix , {
 "LED Matrix" , "btgatt.microbit.led_matrix" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_led_text , {
 "LED Text" , "btgatt.microbit.led_text" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_scrolling_delay , {
 "Scrolling Delay" , "btgatt.microbit.scrolling_delay" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_milliseconds , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_microbit_requirements , {
 "MicroBit Requirements" , "btgatt.microbit.microbit_requirements" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_microbit_event , {
 "MicroBit Event" , "btgatt.microbit.microbit_event" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_client_requirements , {
 "Client Requirements" , "btgatt.microbit.client_requirements" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_client_event , {
 "Client Event" , "btgatt.microbit.client_event" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_dfu_control , {
 "DFU Control" , "btgatt.microbit.dfu_control" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_temperature_value , {
 "Temperature" , "btgatt.microbit.temperature.value" , FT_INT8 , BASE_DEC | BASE_UNIT_STRING , & units_degree_celsius , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gatt_microbit_temperature_period , {
 "Temperature Period" , "btgatt.microbit.temperature.period" , FT_UINT16 , BASE_DEC | BASE_UNIT_STRING , & units_milliseconds , 0x0 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_btgatt , & ett_btgatt_microbit_accelerometer , & ett_btgatt_microbit_magnetometer , & ett_btgatt_microbit_pin_data , & ett_btgatt_microbit_pin_ad_config , & ett_btgatt_microbit_pin_io_config , }
 ;
 proto_btgatt = proto_register_protocol ( "Bluetooth GATT Attribute Protocol" , "BT GATT" , "btgatt" ) ;
 btgatt_handle = register_dissector ( "btgatt" , dissect_btgatt , proto_btgatt ) ;
 proto_register_field_array ( proto_btgatt , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 }