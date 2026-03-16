static void col_append_info_by_handle ( packet_info * pinfo , guint16 handle , bluetooth_data_t * bluetooth_data ) {
 bluetooth_uuid_t service_uuid ;
 bluetooth_uuid_t characteristic_uuid ;
 bluetooth_uuid_t uuid ;
 service_uuid = get_service_uuid_from_handle ( pinfo , handle , bluetooth_data ) ;
 characteristic_uuid = get_characteristic_uuid_from_handle ( pinfo , handle , bluetooth_data ) ;
 uuid = get_uuid_from_handle ( pinfo , handle , bluetooth_data ) ;
 if ( ! memcmp ( & service_uuid , & uuid , sizeof ( uuid ) ) ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ", Handle: 0x%04x (%s)" , handle , print_uuid ( & uuid ) ) ;
 }
 else if ( ! memcmp ( & characteristic_uuid , & uuid , sizeof ( uuid ) ) ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ", Handle: 0x%04x (%s: %s)" , handle , print_uuid ( & service_uuid ) , print_uuid ( & uuid ) ) ;
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , ", Handle: 0x%04x (%s: %s: %s)" , handle , print_uuid ( & service_uuid ) , print_uuid ( & characteristic_uuid ) , print_uuid ( & uuid ) ) ;
 }
 }