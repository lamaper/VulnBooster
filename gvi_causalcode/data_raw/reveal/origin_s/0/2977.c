static bool master_service_settings_check ( void * _set , pool_t pool ATTR_UNUSED , const char * * error_r ) {
 struct master_service_settings * set = _set ;
 int facility ;
 if ( * set -> log_path == '\0' ) {
 set -> log_path = "syslog" ;
 }
 if ( ! syslog_facility_find ( set -> syslog_facility , & facility ) ) {
 * error_r = t_strdup_printf ( "Unknown syslog_facility: %s" , set -> syslog_facility ) ;
 return FALSE ;
 }
 return TRUE ;
 }