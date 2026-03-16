TSReturnCode TSPluginRegister ( const TSPluginRegistrationInfo * plugin_info ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) plugin_info ) == TS_SUCCESS ) ;
 if ( ! plugin_reg_current ) {
 return TS_ERROR ;
 }
 plugin_reg_current -> plugin_registered = true ;
 if ( plugin_info -> plugin_name ) {
 plugin_reg_current -> plugin_name = ats_strdup ( plugin_info -> plugin_name ) ;
 }
 if ( plugin_info -> vendor_name ) {
 plugin_reg_current -> vendor_name = ats_strdup ( plugin_info -> vendor_name ) ;
 }
 if ( plugin_info -> support_email ) {
 plugin_reg_current -> support_email = ats_strdup ( plugin_info -> support_email ) ;
 }
 return TS_SUCCESS ;
 }