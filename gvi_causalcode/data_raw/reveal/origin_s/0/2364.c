void proto_reg_handoff_btatt ( void ) {
 gint i_array ;
 GString * uuid_str = g_string_new ( "" ) ;
 http_handle = find_dissector_add_dependency ( "http" , proto_btatt ) ;
 usb_hid_boot_keyboard_input_report_handle = find_dissector_add_dependency ( "usbhid.boot_report.keyboard.input" , proto_btatt ) ;
 usb_hid_boot_keyboard_output_report_handle = find_dissector_add_dependency ( "usbhid.boot_report.keyboard.output" , proto_btatt ) ;
 usb_hid_boot_mouse_input_report_handle = find_dissector_add_dependency ( "usbhid.boot_report.mouse.input" , proto_btatt ) ;
 dissector_add_uint ( "btl2cap.psm" , BTL2CAP_PSM_ATT , btatt_handle ) ;
 dissector_add_uint ( "btl2cap.cid" , BTL2CAP_FIXED_CID_ATT , btatt_handle ) ;
 btatt_tap_handles = register_tap ( "btatt.handles" ) ;
 for ( i_array = 0 ;
 bluetooth_uuid_vals [ i_array ] . strptr != NULL ;
 i_array += 1 ) {
 gchar * name ;
 gchar * short_name ;
 gchar * abbrev ;
 dissector_handle_t handle_tmp ;
 gint proto_tmp ;
 if ( bluetooth_uuid_vals [ i_array ] . value < 0x1800 ) {
 continue ;
 }
 if ( ( ( bluetooth_uuid_vals [ i_array ] . value & 0xFF00 ) == 0x2700 ) || ( ( bluetooth_uuid_vals [ i_array ] . value & 0xFF00 ) == 0xFD00 ) || ( ( bluetooth_uuid_vals [ i_array ] . value & 0xFF00 ) == 0xFE00 ) ) {
 continue ;
 }
 g_string_printf ( uuid_str , "0x%04x" , bluetooth_uuid_vals [ i_array ] . value ) ;
 name = wmem_strconcat ( wmem_epan_scope ( ) , "Bluetooth GATT Attribute " , bluetooth_uuid_vals [ i_array ] . strptr , " (UUID " , uuid_str -> str , ")" , NULL ) ;
 short_name = wmem_strconcat ( wmem_epan_scope ( ) , "BT GATT " , bluetooth_uuid_vals [ i_array ] . strptr , " (UUID " , uuid_str -> str , ")" , NULL ) ;
 abbrev = wmem_strconcat ( wmem_epan_scope ( ) , "btgatt.uuid" , uuid_str -> str , NULL ) ;
 proto_tmp = proto_register_protocol ( name , short_name , abbrev ) ;
 handle_tmp = register_dissector ( abbrev , dissect_btgatt , proto_tmp ) ;
 dissector_add_for_decode_as ( "btatt.handle" , handle_tmp ) ;
 }
 g_string_free ( uuid_str , TRUE ) ;
 }