static void new_interface ( extcap_parameters * extcap_conf , const gchar * interface_id , const gchar * model_name , const gchar * serial_number , const gchar * display_name ) {
 char * interface = g_strdup_printf ( "%s-%s" , interface_id , serial_number ) ;
 char * ifdisplay = g_strdup_printf ( "%s %s %s" , display_name , model_name , serial_number ) ;
 if ( is_specified_interface ( interface , INTERFACE_ANDROID_BLUETOOTH_HCIDUMP ) || is_specified_interface ( interface , INTERFACE_ANDROID_BLUETOOTH_EXTERNAL_PARSER ) || is_specified_interface ( interface , INTERFACE_ANDROID_BLUETOOTH_BTSNOOP_NET ) ) {
 extcap_base_register_interface_ext ( extcap_conf , interface , ifdisplay , 99 , "BluetoothH4" , "Bluetooth HCI UART transport layer plus pseudo-header" ) ;
 }
 else if ( is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_MAIN ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_SYSTEM ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_RADIO ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_EVENTS ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_MAIN ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_SYSTEM ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_RADIO ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_EVENTS ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_CRASH ) ) {
 extcap_base_register_interface ( extcap_conf , interface , ifdisplay , 252 , "Upper PDU" ) ;
 }
 else if ( is_specified_interface ( interface , INTERFACE_ANDROID_WIFI_TCPDUMP ) ) {
 extcap_base_register_interface ( extcap_conf , interface , ifdisplay , 1 , "Ethernet" ) ;
 }
 g_free ( interface ) ;
 g_free ( ifdisplay ) ;
 }