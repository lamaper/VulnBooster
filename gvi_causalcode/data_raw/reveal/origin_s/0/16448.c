static void decode_zcl_appl_stats_utc_time ( gchar * s , guint32 value ) {
 if ( value == ZBEE_ZCL_APPL_STATS_INVALID_TIME ) g_snprintf ( s , ITEM_LABEL_LENGTH , "Invalid UTC Time" ) ;
 else {
 gchar * utc_time ;
 value += ZBEE_ZCL_NSTIME_UTC_OFFSET ;
 utc_time = abs_time_secs_to_str ( NULL , value , ABSOLUTE_TIME_LOCAL , TRUE ) ;
 g_snprintf ( s , ITEM_LABEL_LENGTH , "%s" , utc_time ) ;
 wmem_free ( NULL , utc_time ) ;
 }
 }