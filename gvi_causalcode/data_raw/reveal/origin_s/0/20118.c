void proto_reg_handoff_adb ( void ) {
 adb_service_handle = find_dissector_add_dependency ( "adb_service" , proto_adb ) ;
 dissector_add_for_decode_as ( "tcp.port" , adb_handle ) ;
 dissector_add_for_decode_as ( "usb.device" , adb_handle ) ;
 dissector_add_for_decode_as ( "usb.product" , adb_handle ) ;
 dissector_add_for_decode_as ( "usb.protocol" , adb_handle ) ;
 proto_tcp = proto_get_id_by_filter_name ( "tcp" ) ;
 proto_usb = proto_get_id_by_filter_name ( "usb" ) ;
 }